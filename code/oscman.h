/**
 * \file oscman.h
 * \class OscMan
 *
 * \brief Class which parses the incoming OSC messages.
 *
 * \author Henrik von Coler
 *
 * \date 2019/03/18$
 *
 */

#ifndef OSCMAN_H
#define OSCMAN_H

 
// works with 'self built'

#include <lo/lo.h>
#include <lo/lo_cpp.h>

#include<iostream>
#include<vector>
#include<string>
#include <stdexcept>


class OscMan
{

private:



    /// the port to be opened
    int port;

    lo::ServerThread *st;

    double pos [4];


    ///
    ////// \brief OscMan::pos_callback
    ////// \param path
    ////// \param types
    ////// \param argv
    ////// \param argc
    ////// \param data
    ////// \param user_data
    ////// \return
    static int pos_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);

public:

    ///
    /// \brief OscMan::OscMan
    /// \param p
    ///
    OscMan(int p);

    ///
    /// \brief OscMan::get_pos
    /// \return
    ///
    double get_pos();



};

#endif
