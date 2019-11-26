/*******************************************************************************
 *  Audio output interface
 *  © 2017-2019, Sauron
 ******************************************************************************/

#ifndef __AUDIOOUTPUT_HPP
#define __AUDIOOUTPUT_HPP

#include <ao/ao.h>
#include <initializer_list>
#include <utility>

/**/
class AudioOutput {
public:
    /**/
    typedef ao_sample_format SampleFormat;
    /**/
    typedef std::pair<const char *, const char *> Option;
    /**/
    typedef std::initializer_list<Option> Options;
    /**/
    enum Exception {
        NODRIVER=AO_ENODRIVER,
        NOTFILE=AO_ENOTFILE,
        NOTLIVE=AO_ENOTLIVE,
        BADOPTION=AO_EBADOPTION,
        OPENDEVICE=AO_EOPENDEVICE,
        OPENFILE=AO_EOPENFILE,
        FILEEXISTS=AO_EFILEEXISTS,
        BADFORMAT=AO_EBADFORMAT,
        FAIL=AO_EFAIL
    };
    /**/
    enum ByteFormat {
        LITTLE=AO_FMT_LITTLE,
        BIG=AO_FMT_BIG,
        NATIVE=AO_FMT_NATIVE
    };
    /**/
    AudioOutput(const SampleFormat &format);
    /**/
    AudioOutput(int driverId, const SampleFormat &format);
    /**/
    AudioOutput(const SampleFormat &format, const Options &options);
    /**/
    AudioOutput(int driverId, const SampleFormat &format, const Options &options);
    /**/
    ~AudioOutput();
    /**/
    int play(const void * samples, size_t length);
    /**/
    static int defaultDriverId();
    /**/
    static int driverId(const char * shortName);
    
private:
    ao_device * device;
};

#endif
