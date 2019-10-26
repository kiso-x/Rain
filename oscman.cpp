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
    reset = 1;


    st = new lo::ServerThread(port);

    if (st->is_valid())
    {
        st->add_method("/texture", "f", texture_callback, this);
        st->add_method("/cutoff", "f", cutoff_callback, this);
        st->add_method("/mode", "f", mode_callback, this);
        st->add_method("/start", "f", start_callback, this);
        st->add_method("/length", "f", length_callback, this);
        st->add_method("/pitch", "f", pitch_callback, this);
        st->add_method("/bit", "f", bit_callback, this);
        st->add_method("/funky", "f", funky_callback, this);
        st->add_method("/reset", "f", reset_callback, this);
        st->add_method("/spread", "f", spread_callback, this);

        st->start();
        std::cout << "Started OSC Server!" << std::endl;
    }
    else
        throw std::invalid_argument("OSC server not started - possibly a bad port!");
}


int OscMan::texture_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed Texture to: " << argv[0]->f << std::endl;
    statCast->texture = argv[0]->f;
}

int OscMan::cutoff_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed Cutoff Frequency to: " << argv[0]->f << std::endl;
    statCast->cutoff = argv[0]->f;
}

int OscMan::mode_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed playback mode to: " << argv[0]->f << std::endl;
    statCast->mode = (int) argv[0]->f;
}

int OscMan::start_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed Start Position to: " << argv[0]->f << std::endl;
    statCast->start_loop = argv[0]->f;
}

int OscMan::length_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Changed Length to: " << argv[0]->f << std::endl;

    statCast->length_loop = argv[0]->f;
}


int OscMan::pitch_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "Pitch: " << argv[0]->f << std::endl;

    statCast->pitch = argv[0]->f;
}

int OscMan::bit_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    std::cout << "BIT: " << argv[0]->f << std::endl;

    statCast->bit = (int) argv[0]->f;
}

int OscMan::funky_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    
    if((int) argv[0]->f == 1)
    {
        std::cout << "You've got the Funk activated!" << std::endl;    
    }
    
    statCast->funk = (int) argv[0]->f;
    std::cout << "Funk: " << statCast->funk << std::endl;
}

int OscMan::reset_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);

    statCast->reset++;
    std::cout << "Reeeeset!" << std::endl;    
}

int OscMan::spread_callback(const char *path, const char *types, lo_arg ** argv,
                           int argc, void *data, void *user_data )
{
    OscMan* statCast = static_cast<OscMan*>(user_data);
    statCast->spread = argv[0]->f;    
}


double OscMan::get_texture()
{
    return texture;
}

double OscMan::get_cutoff()
{
    return cutoff;
}

double OscMan::get_start()
{
    return start_loop;
}

double OscMan::get_length()
{
    return length_loop;
}

int OscMan::get_mode()
{
    return mode;
}


double OscMan::get_pitch()
{
    return this->pitch;
}

int OscMan::get_bit()
{
    return bit;
}

int OscMan::get_funky()
{
    return funk;
}

int OscMan::get_reset()
{
    return reset;
}

double OscMan::get_spread()
{
    return reset;
}
