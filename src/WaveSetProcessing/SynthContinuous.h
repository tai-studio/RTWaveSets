#ifndef SYNTHCONTINUOUS_H
#define SYNTHCONTINUOUS_H

#include "WsStorage.h"
#include "WaveSetStorage/WsStorageDualBuf.h"
#include "WaveSetIterator.h"

class SynthContinuous
{
private:
    WsStorageDualBuf* wsData;

    /** Iterator for WS Playbacks */
    WaveSetIterator wsIterator;

    /** Variables for next Playback */
    int nextWsIdx;
    int nextGroupSize;
    float nextRate;
    int nextRepeat;

    void playGroup(WaveSetIterator* wsIterator,float repeat,int groupSize,int wsIdx ,float rate);
    WaveSetPlay alignGroup(int wsIdx, int groupSize);
    float getSample(double idx);
public:
    SynthContinuous(WsStorage* wsData);
    void setNext(int idxIn, int groupSize, float rate, int repeat);
    float getNextOutput();
};

#endif // SYNTHCONTINUOUS_H
