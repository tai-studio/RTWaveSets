#include "SynthContinuous.h"

SynthContinuous::SynthContinuous(WsStorage* wsData) : Synth(wsData)
{
    nextWsIdx = -1;
    nextGroupSize = -1;
    nextRate = 1.0;
    nextRepeat = 0;
}

void SynthContinuous::setNext(int wsIdx, int groupSize, float rate, int repeat)
{
    this->nextWsIdx = wsIdx;
    this->nextGroupSize = groupSize;
    this->nextRate = rate;
    this->nextRepeat = repeat;
}

float SynthContinuous::getNextOutput()
{

    // Start next Playback on End if valid index is available
    if(this->wsPlayer.endOfPlay() && nextWsIdx>=0){
        initPlayback(&wsPlayer,nextRepeat,nextGroupSize,nextWsIdx ,nextRate);
    }

    float outSample = 0.0;

    // Play Wavesets from Iterator
    try
    {
        if(!wsPlayer.endOfPlay()) {
            outSample = wsPlayer.nextSample();
        }
    }
    catch(...)
    {
        // TODO move exeption handling with stop to WsPlayer
        printf("Waveset playback failed! (unknown exception)\n");
        wsPlayer = WsPlayer(); // stop playback by resetting
    }


    return outSample;
}

