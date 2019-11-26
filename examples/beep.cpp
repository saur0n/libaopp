#include <ao/AudioOutput.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::cerr;
using std::endl;
using std::vector;

static const unsigned SAMPLE_RATE=44100;

int main(int argc, char ** argv) {
    try {
        if (argc<3) {
            cerr << "Usage: " << argv[0] << " FREQUENCY DURATION" << endl;
            return 1;
        }
        
        unsigned frequency=std::stoul(argv[1]);
        unsigned duration=std::stoul(argv[2]);
        
        // Prepare sample data
        vector<int16_t> soundData(SAMPLE_RATE*duration);
        cerr << soundData.size() << " samples" << endl;
        for (size_t i=0; i<soundData.size(); i++) {
            float t=float(i)/SAMPLE_RATE;
            soundData[i]=(1<<14)*sin(2*M_PI*t*frequency);
        }
        
        // Play the sound
        AudioOutput audioOutput({16, SAMPLE_RATE, 1, AudioOutput::NATIVE, nullptr});
        audioOutput.play(soundData.data(), soundData.size());
        
        return 0;
    }
    catch (const std::exception &e) {
        cerr << argv[0] << ": error: " << e.what() << endl;
        return 2;
    }
}
