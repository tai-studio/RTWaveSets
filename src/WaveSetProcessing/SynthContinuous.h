#ifndef SYNTHCONTINUOUS_H
#define SYNTHCONTINUOUS_H

#include "WsStorage.h"
#include "WsPlayer.h"
#include "Synth.h"


class SynthContinuous : public Synth
{
private:

    /** Iterator for WS Playbacks */
    WsPlayer wsIterator;

    /** Variables for next Playback */
    int nextWsIdx;
    int nextGroupSize;
    float nextRate;
    int nextRepeat;

public:
    SynthContinuous(WsStorage* wsData);
    void setNext(int idxIn, int groupSize, float rate, int repeat);
    float getNextOutput();
};

#endif // SYNTHCONTINUOUS_H
