/**
*
* \file  grainplayer.cpp
* \class GrainPlayer
*
* \brief The granular player class,
*        holding a SingleSound and an
*        array of window functions, representing
*        the grains.
*
* \author Henrik von Coler modified by Marquis Fields and Malte Schneider
*
* \date  2019/10/04
*
*/


#include "grainplayer.h"

using std::cout;
using std::endl;

GrainPlayer::GrainPlayer(std::string filePath, int fs, int win_size, int ch)
{

    cout << "Creating GrainPlayer with " << win_size << " samples window size! " << endl;

    nWindows = 4;

    sample   = new SingleSample(filePath, fs);

    windows  = new TriangularWindow[nWindows];
    
    winsize = win_size;
    N = sample->get_nFrames();

    cout << "N: " << N << " Samples" << endl;
    
    loop_start = 0;
    looplength = N;
    alternator = 0;
    channel = ch;


    

    set_mode(0);

    for(int i=0; i<nWindows; i++)
    {
        windows[i].initialize(winsize, loop_start, looplength, playback_mode, spread*i*winsize);
    }

}



double GrainPlayer::get_sample()
{
    double output = 0;

    for(int windowCNT=0; windowCNT<nWindows; windowCNT++)
    {
        if(reset == 1 && tmpreset < 4)
        {
            if(windowCNT == 0) windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start);
            else  windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start + spread* windowCNT* winsize);
            tmpreset++;
        }

        if(funk == 1)
        {
            windows[windowCNT].set_playback_mode(rand() % (2 + 1));
            playback_mode = windows[windowCNT].get_playback_mode();
        }

        if(playback_mode == 2)
        {
            windows[windowCNT].set_playback_mode(alternator);
        }
        else
        {
            windows[windowCNT].set_playback_mode(playback_mode);
        }

        windows[windowCNT].set_start(loop_start, N);
        windows[windowCNT].set_length(looplength, N);
        
        double tmpGain = windows[windowCNT].get_value();
        
        int tmpPos     = windows[windowCNT].get_relative_position();

        if(tmpPos >= 0 && tmpPos <= N)
        {
            if(sample->get_nChannels() == 1) output += tmpGain * sample->get_sample(0,tmpPos);
            else output += tmpGain * sample->get_sample(channel,tmpPos);
        }

        int step = 0;

        switch (playback_mode)
        {
        case 0:
        {
            step = windows[windowCNT].step_forward();

            if(step > 0)
            {   
                if (step == 2)
                {
                    if(windowCNT == 0) windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start);
                    else  windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start + spread* windowCNT* winsize);
                }
                else
                {
                    windows[windowCNT].move_relative_position(relative_stepsize,N);
                }
            }
            break;
        }
        case 1:
        {
            step = windows[windowCNT].step_backward();

            if(step > 0)
            {   
                if (step == 4)
                {
                    if(windowCNT == 0) windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start);
                    else  windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start + spread* windowCNT* winsize);
                }
                else
                {
                    windows[windowCNT].move_relative_position(relative_stepsize,N);
                }
            }
            break;
        }
        case 2:
        {
            if(alternator == 0) step = windows[windowCNT].step_forward();
            else if(alternator == 1) step = windows[windowCNT].step_backward();

            windows[windowCNT].tmp_mode = 2;
            
            
            if(step > 0)
            {   
                if (step == 2)
                {
                    if(windowCNT == 0) windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start);
                    else  windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start + spread* windowCNT* winsize);
                    set_mode(1);
                    alternator = 1;
                }
                
                else if(step == 4)
                {
                    if(windowCNT == 0) windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start);
                    else  windows[windowCNT].initialize(winsize, loop_start, looplength, playback_mode, loop_start + spread* windowCNT* winsize);
                    set_mode(0);
                    alternator = 0;
                }
                
                else
                {
                    windows[windowCNT].move_relative_position(relative_stepsize,N);
                }
            }
            break;        
        }
        }
    }

    if(reset == 1) return 0;
    else return output * .25;

}

void GrainPlayer::set_relative_distance(double r)
{
    if (funk == 1)
    {
        srand(time(0));
        double ran = (rand() % 5-.01 +1) + .1;
        relative_stepsize = pitch * (ran * (double)rand() / RAND_MAX);
        cout << relative_stepsize << endl;
    }
    else
    {
        relative_stepsize = pitch * r;
    }
}

void GrainPlayer::set_mode(int m)
{
    playback_mode = m;
}

void GrainPlayer::set_length(double l)
{
    looplength = (int) l*(N/100);
}

void GrainPlayer::set_start(double s)
{
    loop_start = (int) s*(N/100);
}

void GrainPlayer::set_pitch(double p)
{
    if(p <= 0) pitch = 1;
    else pitch = p;
}

void GrainPlayer::set_funk(int f)
{
    if(f == 1) funk = f;
    else funk = 0;
    
}
void GrainPlayer::set_reset(int r)
{
    if(r %2 == 0)
    {
        reset = 1;
    }
    else
    {
        reset = 0;
        tmpreset = 0;
    }
}

void GrainPlayer::set_spread(double s)
{
    spread = s;
}

