#ifndef RTWAVESETPLAYERREPEAT_H
#define RTWAVESETPLAYERREPEAT_H

#include "RTWaveSetPlayer.h"

struct RTWaveSetPlayerRepeat : public RTWaveSetPlayer  {
    int lastXingIdx;
};

void RTWaveSetPlayerRepeat_Ctor(RTWaveSetPlayerRepeat *unit);
void RTWaveSetPlayerRepeat_next(RTWaveSetPlayerRepeat *unit, int inNumSamples);
void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit);
void RTWaveSetPlayerRepeat_playNextWS(RTWaveSetPlayerRepeat *unit,int repeat, int numWS, int xingIdx);

#endif // RTWAVESETPLAYERREPEAT_H
