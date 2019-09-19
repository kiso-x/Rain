/**
 * \file oscman.cpp
 * \class OscMan
 *
 * \brief Class which parses the incoming OSC messages.
 *
 * \author Henrik von Coler
 *
 * \date 2019/03/18
 *
 */

#include "oscman.h"



OscMan::OscMan(int p)
{

    port  = p;

    // Grainplayer 1
    double pos [4] = {0., 0., 0., 0.};



    st = new lo::ServerThread(port);

    if (st->is_valid())
    {
        // Add the example handler to the server!
        // Grainplayer 1
        st->add_method("/pos", "f", pos_callback, this);


        // start, obviously
        st->start();
        std::cout << "Started OSC Server!" << std::endl;

    }
    else
        throw std::invalid_argument("OSC server not started - possibly a bad port!");
}

// Callback Methods

// Grainplayer 1
int OscMan::pos_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    // Do a static cast
    OscMan* statCast = static_cast<OscMan*>(user_data);
    std::cout << "Changed Position to: " << argv[0]->f  << " in Grainplayer: " << argv[0]->f << std::endl;
    //statCast->pos1[(int) argv[0]->f] = argv[1]->f;
    statCast->pos[0] = argv[0]->f;
}





// get Methods

// Grainplayer 1

double OscMan::get_pos()
{
    return pos [0];
}


