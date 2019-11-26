/*******************************************************************************
 *  Audio output interface
 *  © 2017, Sauron
 ******************************************************************************/

#include "AudioOutput.hpp"

static ao_device * openLive(int driverId, const AudioOutput::SampleFormat &format, ao_option * options=nullptr) {
    return ao_open_live(driverId, &const_cast<AudioOutput::SampleFormat &>(format), options);
}

AudioOutput::AudioOutput(const SampleFormat &format) :
        AudioOutput(defaultDriverId(), format) {}

AudioOutput::AudioOutput(int driverId, const SampleFormat &format) :
        device(openLive(driverId, format)) {
    if (!device)
        throw Exception(errno);
}

AudioOutput::AudioOutput(int driverId, const SampleFormat &format,
        const Options &options) : device(nullptr) {
    throw "not supported yet";
}

AudioOutput::~AudioOutput() {
    ao_close(device);
}

int AudioOutput::play(const void * samples, size_t length) {
    return ao_play(device, (char *)(samples), length);
}

int AudioOutput::defaultDriverId() {
    return ao_default_driver_id();
}

int AudioOutput::driverId(const char * shortName) {
    return ao_driver_id(shortName);
}

/******************************************************************************/

__attribute__((constructor))
static void initialize() {
    ao_initialize();
}

__attribute__((destructor))
static void terminate() {
    ao_shutdown();
}
