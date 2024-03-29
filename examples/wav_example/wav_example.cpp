/**
*
* \file  wav_example.cpp
* \class WavExample
*
* \brief Read a wave file and play it back in a loop.
*
* \author Henrik von Coler
*
* \date $Date: 2019/03/18 $
*
*/

#include"wav_example.h"

using std::cout;
using std::endl;

WavExample::WavExample(std::string filename){

    // creating an OSC manager instance
    oscman = new OscMan(5111);

    this->client = jack_client_open("WAV_Example", JackNullOption, &status, NULL);

    fs = jack_get_sample_rate(client);



    // hard coded for now
    sample = new SingleSample(filename, fs);

    nChannels = sample->get_nChannels();

    cout << "Starting Jack Client! " << endl;


    jack_set_process_callback(this->client, this->callback_process, this);

    output_port = new jack_port_t*[nChannels];

    for (int i=0; i<nOutputs; i++)
    {
        std::string tmp_str = "output_" + std::to_string(i+1);
        output_port[i] = jack_port_register (client, tmp_str.c_str(),
                                             JACK_DEFAULT_AUDIO_TYPE,
                                             JackPortIsOutput, 0);
    }

    jack_activate(this->client);

    jack_connect(client, jack_port_name(output_port[0]), "system:playback_1");
    jack_connect(client, jack_port_name(output_port[1]), "system:playback_2");

    sleep(-1);

}


int WavExample::process (jack_nframes_t nframes)
{


    // allocate output buffer array
    jack_default_audio_sample_t **out = new jack_default_audio_sample_t*[nChannels];
    for ( int i=0 ; i<nChannels; i++)
    {
        // buffer size can change
        out[i] = (jack_default_audio_sample_t *) jack_port_get_buffer(this->output_port[i], jack_get_buffer_size(client));
    }


    sample->set_rate(oscman->get_speed());

    // loop over all samples of output buffer
    for(int sampCNT=0; sampCNT<nframes; sampCNT++)
    {
        double tmpPos = sample->get_pos();

        for(int chanCNT=0; chanCNT<nChannels; chanCNT++)
        {
            out[chanCNT][sampCNT] = sample->get_sample(chanCNT, tmpPos);
        }

        sample->step();
    }
    return 0;
}


int WavExample::callback_process(jack_nframes_t x, void* object)
{
    return static_cast<WavExample*>(object)->process(x);
}

