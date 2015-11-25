#ifndef SPEECHREG_RECORDER_H
#define SPEECHREG_RECORDER_H


#include <stdio.h>
#include <stdlib.h>
#include <iosfwd>
#include <fstream>
#include "portaudio.h"
#include "Record.h"

#include <boost/circular_buffer.hpp>
#include <list>

class Recorder {

    PaStreamParameters  inputParameters;
    PaStream*           stream;

    bool recording = false;

    static int recordCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData);

    std::list<std::vector<double>> dataSegments_;

public:
    Recorder(unsigned sampleRate = 8000);

    virtual ~Recorder();

    void record();

    std::list<std::vector<double>>& dataSegments() {
        return dataSegments_;
    }
};


#endif //SPEECHREG_RECORDER_H
