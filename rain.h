/**
* \file rain.h
* \class Rain
*
* \brief Read a wave file and play it back in a granular style, with modification through OSC.
*
* \author Henrik von Coler modified by Marquis Fields and Malte Schneider
*
* \date 2019/10/04
*
*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include<jack/jack.h>

#include "oscman.h"
#include "grainplayer.h"
#include "Biquad.h"

using std::cout;
using std::endl;

class Rain{

private:

    ///
    /// \brief
    /// creates an GrainPlayer array with all necessary parameters
    GrainPlayer *grainer[2];

    ///
    /// \brief
    /// filter is a lowpass filter with variable cutoff frequency
    Biquad *filter;

    ///
    /// \brief
    /// sample rate of the jack server
    int fs        = 0;

    ///
    /// \brief
    /// gain of bit crushed output
    double crush_gain        = 0;

    ///
    /// \brief
    ///  number off jack output ports
    int nOutputs  = 2;

    ///
    /// \brief
    /// number of channels in the sample
    int nChannels;

    ///
    /// \brief
    /// cutoff represents the cutoff frequency of the lowpass fitler
    double cutoff;

    ///
    /// \brief
    /// determines bit depth of bitcrushing
    int bit;

    ///
    /// \brief
    /// the jack output ports
    const char **ports;

    ///
    /// \brief pointer to Jack client
    jack_client_t   *client;

    ///
    /// \brief Jack status
    jack_status_t   status;

    ///
    /// \brief pointer to Jack audio output port
    jack_port_t  **output_port;

    /// 
    /// \brief pointer to OSC manager object
    OscMan *oscman;

    ///
    /// \brief get the next buffer from the sample and playback
    /// \param nframes buffer size
    /// \return output of rain
    int process(jack_nframes_t nframes);

    ///
    /// \brief reduce bit depth of input sample
    /// \param sample current sample to be crushed
    /// \return bitcrushed input sample
    double crush(double sample);

    ///
    /// \brief sets gain of bitcrushed signale in dependence of filter cutoff frequency
    /// \param fc filter cutoff frequency
    void set_gain(double fc);



    ///
    /// \brief 
    /// \param x
    /// \param object
    static int callback_process(jack_nframes_t x, void* object);

public:

    ///
    /// \brief Constructor
    /// \param filename path to wav file
    /// \param win_size window size of triangular window
    Rain(std::string filename, int win_size);

};



