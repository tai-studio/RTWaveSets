#ifndef RTWAVESETPLAYERREPEAT_H
#define RTWAVESETPLAYERREPEAT_H

#include "RTWaveSetPlayer.h"

#define RTWaveSetPlayerRepeat_NumIterators 10

struct RTWaveSetPlayerRepeat : public RTWaveSetPlayer  {


    int lastXingIdx;

    /** Previous Trigger Input */
    float prevTrig;


    WaveSetIterator wsIterator;

    /** Iterators for parallel WS Playbacks */
    WaveSetIterator wsIterators[RTWaveSetPlayerRepeat_NumIterators];
};

void RTWaveSetPlayerRepeat_Ctor(RTWaveSetPlayerRepeat *unit);
void RTWaveSetPlayerRepeat_next(RTWaveSetPlayerRepeat *unit, int inNumSamples);
void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit);
void RTWaveSetPlayerRepeat_playNextWS(WaveSetIterator* wsi, RTWaveSetPlayerRepeat *unit,int repeat, int numWS, int xingIdx);

#endif // RTWAVESETPLAYERREPEAT_H
