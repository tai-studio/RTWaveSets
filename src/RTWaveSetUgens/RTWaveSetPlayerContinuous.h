#ifndef RTWaveSetPlayerContinuous_H
#define RTWaveSetPlayerContinuous_H

#include "RTWaveSetPlayer.h"
#include "WaveSetProcessing/SynthContinuous.h"

struct RTWaveSetPlayerContinuous : public RTWaveSetPlayer  {

    SynthContinuous wsSynth;
};

void RTWaveSetPlayerContinuous_Ctor(RTWaveSetPlayerContinuous *unit);
void RTWaveSetPlayerContinuous_next(RTWaveSetPlayerContinuous *unit, int inNumSamples);
void RTWaveSetPlayerContinuous_Dtor(RTWaveSetPlayerContinuous *unit);

#endif // RTWaveSetPlayerContinuous_H
