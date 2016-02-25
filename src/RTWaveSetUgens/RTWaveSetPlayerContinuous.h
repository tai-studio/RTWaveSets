#ifndef RTWaveSetPlayerContinuous_H
#define RTWaveSetPlayerContinuous_H

#include "RTWaveSetBase.h"
#include "WaveSetProcessing/SynthContinuous.h"

struct RTWaveSetPlayerContinuous : public RTWaveSetBase {

    SynthContinuous wsSynth;
};

void RTWaveSetPlayerContinuous_Ctor(RTWaveSetPlayerContinuous *unit);
void RTWaveSetPlayerContinuous_next(RTWaveSetPlayerContinuous *unit, int inNumSamples);
void RTWaveSetPlayerContinuous_Dtor(RTWaveSetPlayerContinuous *unit);

#endif // RTWaveSetPlayerContinuous_H
