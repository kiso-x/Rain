/**
*
* \file  grainplayer.h
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


#ifndef GRAINPLAYER_H
#define GRAINPLAYER_H


#include "singlesample.h"
#include "triangularwindow.h"
#include <ctime>

class GrainPlayer
{
public:

    ///
    /// \brief GrainPlayer
    /// the constructor
    /// \param filePath path to the wav file to read
    /// \param fs sampling rate of the JACK server
    /// \param win_size the grain size (size of the window)
    /// \param nWin the number of grains to be used
    ///
    GrainPlayer(std::string filePath, int fs, int win_size, int ch);

    ///
    /// \brief
    /// get a single sample, using all active grains
    /// \return
    /// a sound sample for the output
    double get_sample();

    ///
    /// \brief
    /// is the step size of the moving playback pos.
    /// \param r relative_stepsize
    void   set_relative_distance(double r);

    ///
    /// \brief
    /// sets the playback mode: forward, backwards or forward-backward played loop
    /// \param m playback_mode
    void   set_mode(int m);

    ///
    /// \brief
    /// sets the looplength
    /// \param l looplength
    void   set_length(double l);

    ///
    /// \brief
    /// sets the start of the loop
    /// \param s loop_start
    void   set_start(double s);

    ///
    /// \brief
    /// sets the playback speed of the loop
    /// \param p pitch
    void   set_pitch(double p);

    ///
    /// \brief
    /// randomized the relative position
    /// \param f funk
    void   set_funk(int f);

    ///
    /// \brief
    /// randomized the relative position
    /// \param r reset
    void   set_reset(int r);

    ///
    /// \brief
    /// randomized the relative position
    /// \param s spread
    void   set_spread(double s);

private:

    ///
    /// \brief 
    /// an instance of the single sample class
    SingleSample *sample;

    ///
    /// \brief 
    /// fraction of window size to shift the window position
    double relative_stepsize;

    ///
    /// \brief 
    /// pointer to an array of windows
    TriangularWindow *windows;

    ///
    /// \brief 
    /// specifies the Length of the playbackloop
    int looplength;

    ///
    /// \brief 
    /// specifies whether the window propagates in a forward or backward loop
    int playback_mode;

    ///
    /// \brief 
    /// specifies the start of the playback loop
    int loop_start;

    ///
    /// \brief
    /// specifies the end of the playback loop
    int loop_end;

    ///
    /// \brief
    /// specifies how many windows contribute to the Grainplayer
    int nWindows;

    ///
    /// \brief
    /// is an auxiliary variable for forward-backward looping
    int alternator;

    ///
    /// \brief
    /// is the playback speed
    double pitch;

    ///
    /// \brief
    /// is the amount of Samples corresponding to the Length of the loaded Wav File
    int N;

    ///
    /// \brief
    /// initiates a random forward movement of the playback window
    int funk;

    ///
    /// \brief
    /// initalizes the windows of the GrainPlayer 
    int reset;

    ///
    /// \brief
    /// modify the distances between the start positions of the loop in relation to each other
    int spread;

    ///
    /// \brief
    /// represents left and right channel of the output
    int channel;

    ///
    /// \brief
    /// represents window size
    int winsize;

    ///
    /// \brief
    /// auxilary variable for reset function
    int tmpreset = 1;

};

#endif // GRAINPLAYER_H
