#ifndef SYNTH_H
#define SYNTH_H

#include "WsPlayer.h"
#include "WaveSetStorage/WsStorageDualBuf.h"

class Synth
{
protected:
    WsStorageDualBuf* wsData;
    int foldIdx(int xingIdx);
    Synth();

public:
    void playGroup(WsPlayer* wsIterator,float repeat,int groupSize,int wsIdx ,float rate);
    WaveSetPlay getGroup(int wsIdx, int groupSize);
    float getSampleInterpolated(double idx);

};

#endif // SYNTH_H
