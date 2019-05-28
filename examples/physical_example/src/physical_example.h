/**
* \file physical_example.h
* \class PhysicalExample
*
* \author Henrik von Coler
*
* \date  2019-05-14
*
*/

#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<unistd.h>
#include<jack/jack.h>

#include"yamlman.h"
#include"midiman.h"
#include"oscman.h"
#include"waveguide.h"


using std::cout;
using std::endl;


class PhysicalExample{

private:

    ///
    /// \brief yaml_manager
    ///        is used for reading the config file
    YamlMan *yaml_manager;

    ///
    /// \brief mode
    ///
    std::string mode;

    ///
    /// \brief fs
    /// the sample rate of the jack server.
    int fs;

    WaveGuide *waveguide_string;


    ///
    /// \brief nChannels
    /// the number of audio channels @todo (should not be hard-coded)
    int nChannels = 2;

    ///
    /// \brief client
    ///         the jack client, obviously
    jack_client_t   *client;

    ///
    /// \brief status
    ///         gets the status from the jack server
    jack_status_t   status;

    ///
    /// \brief output_port
    /// the jack output ports
    jack_port_t     **output_port;

    ///
    /// \brief in
    ///
    /// \brief out
    jack_default_audio_sample_t **in, **out;


    ///  The OSC manager object
    OscMan *oscman;

    ///
    /// \brief midiman
    ///
    MidiMan *midiman;

    ///
    /// \brief process
    ///  The function where the actual
    ///  audio processing takes place.
    /// \param nframes number of frames in the out buffer.
    /// \return
    ///
    int process (jack_nframes_t nframes);

    ///
    /// \brief callback_process
    ///         is used to access the members of this
    ///         class in the static mode
    /// \param x number of samples in the buffer
    /// \param object void pointer
    /// \return
    ///
    static int callback_process(jack_nframes_t x, void* object);

public:

    ///
    /// \brief FmExample
    ///         the constructor
    /// \param yaml_manager
    ///
    PhysicalExample(YamlMan *ym, int ID, string m);

};





