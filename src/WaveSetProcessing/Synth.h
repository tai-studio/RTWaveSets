#ifndef SYNTH_H
#define SYNTH_H

#include "WsPlayer.h"
#include "WsStorage.h"

class Synth
{
protected:
    WsStorage* wsData;

    Synth(WsStorage* wsData);
    int foldIdx(int xingIdx);
    void initPlayback(WsPlayer* wsIterator,float repeat,int groupSize,int wsIdx ,float rate);
};

#endif // SYNTH_H
