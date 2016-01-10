#ifndef RTWaveSetPlayerContinuous_H
#define RTWaveSetPlayerContinuous_H

#include "RTWaveSetPlayer.h"

struct RTWaveSetPlayerContinuous : public RTWaveSetPlayer  {

    /** Iterator for WS Playbacks */
    WaveSetIterator wsIterator;
};

void RTWaveSetPlayerContinuous_Ctor(RTWaveSetPlayerContinuous *unit);
void RTWaveSetPlayerContinuous_next(RTWaveSetPlayerContinuous *unit, int inNumSamples);
void RTWaveSetPlayerContinuous_Dtor(RTWaveSetPlayerContinuous *unit);

#endif // RTWaveSetPlayerContinuous_H
