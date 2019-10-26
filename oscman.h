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


#include <lo/lo.h>
#include <lo/lo_cpp.h>

#include<iostream>
#include<vector>
#include<string>
#include <stdexcept>


class OscMan
{

private:


  ///
  /// \brief
  /// the OSC port to be opened
  int port;

  ///
  /// \brief OSC server thread
  lo::ServerThread *st;

  ///
  /// \brief
  /// texture Slider
  double texture;

  ///
  /// \brief
  /// cutoff Slider
  double cutoff;

  ///
  /// \brief
  /// determines the start of the loop
  double start_loop;

  ///
  /// \brief
  /// determines the end of the loop
  double length_loop;

  ///
  /// \brief
  /// mode Slider
  int mode;

  ///
  /// \brief
  /// pitch Slider
  double pitch;

  ///
  /// \brief
  /// determines the bit depth of the grainer
  int bit;

  ///
  /// \brief
  /// funk initiates a random forward/backward movement of the playback window
  int funk;

  ///
  /// \brief
  /// initalize the windows of the GrainPlayer
  int reset;

  ///
  /// \brief
  /// modify the distances between the start positions of the loop in relation to each other
  double spread;


  ///
  /// \brief OscMan::texture_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int texture_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);

  ///
  /// \brief OscMan::cutoff_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int cutoff_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);

  ///
  /// \brief OscMan::mode_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int mode_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);

  ///
  /// \brief OscMan::start_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int start_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);

  ///
  /// \brief OscMan::length_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int length_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);


  ///
  /// \brief OscMan::pitch_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int pitch_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);

  ///
  /// \brief OscMan::bit_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int bit_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);

  ///
  /// \brief OscMan::q_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int q_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);
  
  ///
  /// \brief OscMan::funky_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int funky_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);
  ///
  /// \brief OscMan::reset_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int reset_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);
  ///
  /// \brief OscMan::win_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int win_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);
  ///
  /// \brief OscMan::spread_callback
  /// \param path
  /// \param types
  /// \param argv
  /// \param argc
  /// \param data
  /// \param user_data
  /// \return
  static int spread_callback(const char *path, const char *types, lo_arg ** argv,
                              int argc, void *data, void *user_data);



public:

  ///
  /// \brief Constructor
  /// \param p OSC port number
  OscMan(int p);

  ///
  /// \brief returns texture input from osc
  /// \return texture
  double get_texture();

  ///
  /// \brief returns filter cutoff input from osc
  /// \return filter cutoff
  double get_cutoff();

  ///
  /// \brief returns loopstart input from osc
  /// \return start_loop
  double get_start();

  ///
  /// \brief returns looplength input from osc
  /// \return length_loop
  double get_length();

  ///
  /// \brief returns loopmode input from osc
  /// \return returns mode
  int get_mode();

  ///
  /// \brief returns pitch input from osc
  /// \return pitch
  double get_pitch();

  /// 
  /// \brief returns loopmode input from osc
  /// \return bit
  int get_bit();

  ///
  /// \brief returns the randomized relative playback position input from osc
  /// \return funk
  int get_funky();

  ///
  /// \brief toggles reset function
  /// \return reset
  int get_reset();

  ///
  /// \brief returns the spread input
  /// \return spread
  double get_spread();    

};

#endif
