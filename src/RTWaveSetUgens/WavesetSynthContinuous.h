#ifndef WavesetSynthContinuous_H
#define WavesetSynthContinuous_H

#include "WavesetBase.h"
#include "WavesetProcessing/SynthContinuous.h"

struct WavesetSynthContinuous : public WavesetBase {

    SynthContinuous wsSynth;
};

void WavesetSynthContinuous_Ctor(WavesetSynthContinuous *unit);
void WavesetSynthContinuous_next(WavesetSynthContinuous *unit, int inNumSamples);
void WavesetSynthContinuous_Dtor(WavesetSynthContinuous *unit);

#endif // WavesetSynthContinuous_H
