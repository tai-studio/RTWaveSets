#ifndef RTWaveSetPlayerTriggered_H
#define RTWaveSetPlayerTriggered_H

#include "RTWaveSetPlayer.h"

#define RTWaveSetPlayerTriggered_NumIterators (512)

struct RTWaveSetPlayerTriggered : public RTWaveSetPlayer  {


    int lastXingIdx;

    /** Previous Trigger Input */
    float prevTrig;

    /** Iterators for parallel WS Playbacks */
    WaveSetIterator wsIterators[RTWaveSetPlayerTriggered_NumIterators];
};

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit);
void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples);
void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit);
void RTWaveSetPlayerTriggered_playNextWS(WaveSetIterator* wsi, RTWaveSetPlayerTriggered *unit,int repeat, int numWS, int xingIdx, float rate);

#endif // RTWaveSetPlayerTriggered_H
