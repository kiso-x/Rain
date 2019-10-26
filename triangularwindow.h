/**
*
* \file  triangularwindow.h
* \class TriangularWindow
*
* \brief A single window (envelope) for granular synthesis.
*
* \author Henrik von Coler modified by Marquis Fields and Malte Schneider
*
* \date  2019/10/04
*
*/

#ifndef TRIANGULARWINDOW_H
#define TRIANGULARWINDOW_H


#include <iostream>
#include <stdlib.h>
#include <ctime>


class TriangularWindow
{

public:

    ///
    /// \brief Constructor
    TriangularWindow();

    ///
    /// \brief initializes window parameters
    /// \param L window length
    /// \param start start position of loop
    /// \param looplength length of loop
    /// \param direction direction of playback
    /// \param startpos relative position of center_offset in wav file
    void initialize(int L, int start, int looplength, int direction, int startpos);

    ///
    /// \brief get the value of the window at the playback_position
    /// \return window value
    double get_value();

    ///
    /// \brief get the relativ playback position of window in wav file
    /// \return relative positon
    int get_relative_position();

    ///
    /// \brief move window position in the wav file
    /// \param p the fraction of the window size to shift the position
    /// \param maxLength the maximum length of the wav file
    void move_relative_position(double p, int maxLength);

    ///
    /// \brief move window position in the wav file
    /// \param p the fraction of the window size to shift the position
    /// \param maxLength the maximum length of the wav file
    /// \param win window size in samples
    void move_relative_position(double p, int maxLength, int win);

    ///
    /// \brief increments playback position
    /// \return returns 1 if end of window is reached
    int step_forward();

    ///
    /// \brief decrements playback position
    /// \return returns 3 if end of window is reached
    int step_backward();

    ///
    /// \brief sets playback loop mode
    /// \param mode the desired playback loop mode
    void set_playback_mode(int mode);

    ///
    /// \brief get the playback loop mode
    /// \return playback_mode
    int get_playback_mode();

    ///
    /// \brief sets playback loop length
    /// \param l desired playback loop length
    /// \param n length of wav file in samples
    void set_length(int l, int n);

    ///
    /// \brief sets playback loop start position
    /// \param l desired playback loop start position
    /// \param n length of wav file in samples
    void set_start(int s, int n);

    ///
    /// \brief
    /// auxiliary variable to control the playbackmode
    int tmp_mode;

private:

    ///
    /// \brief
    /// the length of the window
    int length;

    ///
    /// \brief
    /// the slope of the triangular window
    double m;

    ///
    /// \brief
    /// the position of the window in the wav file
    int center_offset;

    ///
    /// \brief 
    /// is the playback position within the window
    int playback_position;

    ///
    /// \brief 
    /// specifies the Length of the playbackloop
    int looplength;

    ///
    /// \brief
    ///specifies whether the window propagates in a forward or backward loop
    int playback_mode;

    ///
    /// \brief
    /// represets playback loop start position 
    int loop_start;

    ///
    /// \brief
    /// represets playback loop end position 
    int loop_end;

    ///
    /// \brief
    /// represets start position of window in the wav file
    int startpos;
};

#endif // TRIANGULARWINDOW_H
