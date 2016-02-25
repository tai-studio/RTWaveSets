#include "SynthContinuous.h"

SynthContinuous::SynthContinuous(WsStorage* wsData)
{
    this->wsData = (WsStorageDualBuf*) wsData;
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
    if(this->wsIterator.endOfPlay() && nextWsIdx>=0){
        playGroup(&wsIterator,nextRepeat,nextGroupSize,nextWsIdx ,nextRate);
    }

    float outSample = 0.0;

    // Play WaveSets from Iterator
    try
    {
        if(!wsIterator.endOfPlay()) {
            double nextIdx = wsIterator.next();
            if(wsData->audioBuf->isInRange((int)nextIdx)){
                outSample = getSampleInterpolated(nextIdx);
            }
            else{
                printf("WaveSet playback failed! (out of audio buffer Range)\n");
                wsIterator = WsPlayer(); // stop playback by resetting
            }
        }
    }
    catch(...)
    {
        printf("WaveSet playback failed! (unknown exception)\n");
        wsIterator = WsPlayer(); // stop playback by resetting
    }


    return outSample;
}

