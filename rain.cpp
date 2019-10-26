/**
* \file rain.cpp
* \class Rain
*
* \brief Read a wave file and play it back in a granular style, with modification through OSC.
*
* \author Henrik von Coler modified by Marquis Fields and Malte Schneider
*
* \date 2019/10/04
*
*/

#include"rain.h"

using std::cout;
using std::endl;

Rain::Rain(std::string filename, int win_size)
{
    try
    {
        oscman = new OscMan(5112);
    }
    catch(int e)
    {
        cout << "Bad Port!";
    }

    this->client = jack_client_open("Rain", JackNullOption, &status, NULL);
    fs = jack_get_sample_rate(client);

    grainer[0] = new GrainPlayer(filename, fs, win_size, 0);
    grainer[1] = new GrainPlayer(filename, fs, win_size, 1);

    filter = new Biquad();
    nChannels = 2;

    cout << "Starting Jack Client! " << endl;

    jack_set_process_callback(this->client, this->callback_process, this);

    output_port = new jack_port_t*[nChannels];

    for (int i=0; i<nOutputs; i++)
    {
        std::string tmp_str = "output_" + std::to_string(i+1);
        output_port[i] = jack_port_register (client, tmp_str.c_str(),
                                             JACK_DEFAULT_AUDIO_TYPE,
                                             JackPortIsOutput, 0);
    }

    jack_activate(this->client);

    jack_connect(client, jack_port_name(output_port[0]), "system:playback_1");
    jack_connect(client, jack_port_name(output_port[1]), "system:playback_2");

    sleep(-1);
}


int Rain::process (jack_nframes_t nframes)
{
    jack_default_audio_sample_t **out = new jack_default_audio_sample_t*[nChannels];
    for ( int i=0 ; i<nChannels; i++)
    {
        out[i] = (jack_default_audio_sample_t *) jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
    }

    grainer[0]->set_relative_distance(oscman->get_texture());
    grainer[0]->set_mode(oscman->get_mode());
    grainer[0]->set_start(oscman->get_start());
    grainer[0]->set_length(oscman->get_length());
    grainer[0]->set_pitch(oscman->get_pitch());
    grainer[0]->set_funk(oscman->get_funky());
    grainer[0]->set_reset(oscman->get_reset());
    grainer[0]->set_spread(oscman->get_spread());

    grainer[1]->set_relative_distance(oscman->get_texture());
    grainer[1]->set_mode(oscman->get_mode());
    grainer[1]->set_start(oscman->get_start());
    grainer[1]->set_length(oscman->get_length());
    grainer[1]->set_pitch(oscman->get_pitch());
    grainer[1]->set_funk(oscman->get_funky());
    grainer[1]->set_reset(oscman->get_reset());
    grainer[1]->set_spread(oscman->get_spread());

    filter->setFc(oscman->get_cutoff(),fs);
    
    double tmp = 0;
    double tmpl = 0;
    double tmpr = 0;
    double filteredl = 0;
    double filteredr = 0;
    double crushedl = 0;
    double crushedr = 0;


    for(int sampCNT=0; sampCNT<nframes; sampCNT++)
    {
        tmpl = grainer[0]->get_sample();
        tmpr =  grainer[1]->get_sample();

        filteredl = filter->process(tmpl);
        filteredl = filter->process(tmpl);
        
        bit = oscman->get_bit();
        crushedl = this->crush(filteredl);
        crushedr = this->crush(filteredr);

        out[0][sampCNT] = (filteredl + (crush_gain*crushedl))/ sqrt(2);
        out[1][sampCNT] = (filteredr + (crush_gain*crushedr))/ sqrt(2);
    }
    return 0;
}


int Rain::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<Rain*>(object)->process(x);
}

double Rain::crush(double sample)
{
    set_gain(oscman->get_cutoff());
    int max = pow(2, bit)-1;
    double res = round(sample * max);
    res = res / max;
    
    return res;
}

void Rain::set_gain(double fc)
{
    if(fc < 100)
    {
        crush_gain = 1.;
    }
    else if(fc > 10000)
    {
        crush_gain = 0.;
    } 
    else
    {
        crush_gain = ((fc - 100) / (100-10000)) + 1;
    } 
}
