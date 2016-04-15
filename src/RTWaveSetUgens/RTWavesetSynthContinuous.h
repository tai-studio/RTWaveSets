#ifndef RTWavesetSynthContinuous_H
#define RTWavesetSynthContinuous_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/SynthContinuous.h"

struct RTWavesetSynthContinuous : public RTWavesetBase {

    SynthContinuous wsSynth;
};

void RTWavesetSynthContinuous_Ctor(RTWavesetSynthContinuous *unit);
void RTWavesetSynthContinuous_next(RTWavesetSynthContinuous *unit, int inNumSamples);
void RTWavesetSynthContinuous_Dtor(RTWavesetSynthContinuous *unit);

#endif // RTWavesetSynthContinuous_H
