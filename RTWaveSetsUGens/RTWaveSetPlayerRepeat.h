#ifndef RTWAVESETPLAYERREPEAT_H
#define RTWAVESETPLAYERREPEAT_H

#include "RTWaveSetPlayer.h"


struct RTWaveSetPlayerRepeat : public RTWaveSetPlayer  {
};

void RTWaveSetPlayerRepeat_Ctor(RTWaveSetPlayerRepeat *unit);
void RTWaveSetPlayerRepeat_next(RTWaveSetPlayerRepeat *unit, int inNumSamples);
void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit);
void RTWaveSetPlayerRepeat_playNextWS(RTWaveSetPlayerRepeat *unit);

#endif // RTWAVESETPLAYERREPEAT_H
