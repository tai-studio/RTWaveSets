#ifndef RTWaveSetPlayerTriggered_H
#define RTWaveSetPlayerTriggered_H

#include "RTWaveSetPlayer.h"


struct RTWaveSetPlayerTriggered : public RTWaveSetPlayer  {
};

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit);
void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples);
void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit);

#endif // RTWaveSetPlayerTriggered_H
