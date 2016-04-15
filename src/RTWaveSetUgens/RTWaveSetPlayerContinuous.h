#ifndef RTWavesetPlayerContinuous_H
#define RTWavesetPlayerContinuous_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/SynthContinuous.h"

struct RTWavesetPlayerContinuous : public RTWavesetBase {

    SynthContinuous wsSynth;
};

void RTWavesetPlayerContinuous_Ctor(RTWavesetPlayerContinuous *unit);
void RTWavesetPlayerContinuous_next(RTWavesetPlayerContinuous *unit, int inNumSamples);
void RTWavesetPlayerContinuous_Dtor(RTWavesetPlayerContinuous *unit);

#endif // RTWavesetPlayerContinuous_H
