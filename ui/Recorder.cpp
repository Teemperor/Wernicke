#include <iostream>
#include "Recorder.h"


#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)

int Recorder::recordCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    Recorder* data = (Recorder*)userData;
    const SAMPLE* input = (const SAMPLE*) inputBuffer;

    std::vector<double> buffer;
    buffer.resize(framesPerBuffer);

    for (std::size_t i = 0; i < framesPerBuffer; i++) {
        buffer[i] = input[i];
    }

    data->dataSegments_.push_back(buffer);

    std::cout << framesPerBuffer << std::endl;

    return paContinue; // paComplete;
}

void Recorder::record() {

    /*data.maxFrameIndex = totalFrames = seconds * sampleRate;
    data.frameIndex = 0;
    numSamples = totalFrames;
    numBytes = numSamples * sizeof(SAMPLE);

    data.recordedSamples = new SAMPLE[numBytes];
    for(int i=0; i<numSamples; i++ )
        data.recordedSamples[i] = 0;
*/
    int err;

    if (Pa_Initialize() != paNoError )
         throw std::domain_error("Error in Pa_Init");

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
        throw std::domain_error("Error: No default input device.\n");
    }

    inputParameters.channelCount = 1;                    /* mono input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
            &stream,
            &inputParameters,
            NULL,                  /* &outputParameters, */
            16000, // sample rate
            0,
            paClipOff,      /* we won't output out of range samples so don't bother clipping them */
            recordCallback,
            this);
    if (err != paNoError) throw std::domain_error("Error in Pa_OpenStream");

    err = Pa_StartStream( stream );
    if (err != paNoError) throw std::domain_error("Error in Pa_StartStream");
    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);

}

Recorder::Recorder(unsigned sampleRate) {
}

Recorder::~Recorder() {
    int err;
    //while (( err = Pa_IsStreamActive( stream )) == 1 )
    //{
    //    Pa_Sleep(1000);
    //}
    //if (err < 0) throw std::domain_error("Error in Pa_IsStreamActive");

    err = Pa_CloseStream (stream);
    if (err != paNoError) throw std::domain_error("Error in Pa_CloseStream");

    Pa_Terminate();
}