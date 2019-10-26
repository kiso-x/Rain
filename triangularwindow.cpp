/**
*
* \file  triangularwindow.cpp
* \class TriangularWindow
*
* \brief A single window (envelope) for granular synthesis.
*
* \author Henrik von Coler modified by Marquis Fields and Malte Schneider
*
* \date  2019/10/04
*
*/

#include "triangularwindow.h"

using std::cout;
using std::endl;


TriangularWindow::TriangularWindow()
{
}

void TriangularWindow::initialize(int L, int start, int loop, int mode, int startpo)
{
    length              = L;
    playback_mode = mode;
    playback_position   = 0;
    m = 2 / (double) L ;
    looplength = loop;

    if(startpo >= start+loop)
    {
        srand(time(0));
        int ran = (int) (rand() % (loop+1)) + start;
        startpos = ran;
    }
    else startpos = startpo;
    
    
    if(mode == 1)
    {
        loop_end = start;
        loop_start = loop_end + looplength;
        center_offset       = loop_start - startpos;
    }
    
    else
    {
        center_offset       = start + startpos;
        loop_start = start;
        loop_end = start + looplength;
    }
}

double TriangularWindow::get_value()
{
    double gain = 0;
    int ppos = std::abs(playback_position);

    if(ppos <= length/2)
    {
        gain =  m * ppos;
    }
    else
    {
        gain =  1 - m * (ppos - length/2);
    }

    return gain;
}

int TriangularWindow::get_relative_position()
{
    return center_offset + playback_position; 
}

void TriangularWindow::move_relative_position(double p, int maxLength)
{
    if(playback_mode == 0) 
    {   
        center_offset += (int) ((double) length * p);
    }
    else if(playback_mode == 1)
    {
        center_offset -= (int) ((double) length * p);
    }
}



int TriangularWindow::step_forward()
{
    int finished = 0;
    playback_position ++;

    
    if(playback_position>=length)
    {
        playback_position = 0;
        finished = 1;
    }

    if (center_offset+length >= loop_end)
    {
        finished = 2;
    }

    return finished;
}

int TriangularWindow::step_backward()
{
    int finished = 0;
    playback_position--;

    if(playback_position<=-length)
    {
        playback_position = 0;
        finished = 3;
    }
    if (center_offset-length <= loop_end)
    {
        finished = 4;
    }
    return finished;
}


void TriangularWindow::set_playback_mode(int mode)
{  
    if (playback_mode != mode && tmp_mode == 2)
    {
        initialize(this->length, this->center_offset, this->looplength, mode, this->center_offset);
    }
}

int TriangularWindow::get_playback_mode()
{
    return playback_mode;
}

void TriangularWindow::set_start(int s, int n)
{  
    if((playback_mode == 0) and (s not_eq loop_start))
    {        
        loop_start = s;
    }

    if(playback_mode == 1 && s != loop_end)
    {
        loop_end = s;
    }
}

void TriangularWindow::set_length(int len, int n)
{  
    if(playback_mode == 0 && len != looplength)
    {
        looplength = len;

        if(loop_start + looplength > n)
        {
            loop_end = n;
            looplength = n-loop_start;
        }
        else
        {
            loop_end = loop_start + looplength;
        }
    }

    if(playback_mode == 1 && len != looplength)
    {
        if(loop_end + len > n)
        {
            loop_start = n;
        }
        else
        {
            loop_start = loop_end + len;
        }
    }
}



