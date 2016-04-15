#ifndef WavesetSynthTriggered_H
#define WavesetSynthTriggered_H

#include "WavesetBase.h"
#include "WavesetProcessing/SynthParallel.h"

#define WavesetSynthTriggered_NumIterators (512)

struct WavesetSynthTriggered : public WavesetBase  {

    SynthParallel wsSynth;

    /** Previous Trigger Input */
    float prevTrig;

};

void WavesetSynthTriggered_Ctor(WavesetSynthTriggered *unit);
void WavesetSynthTriggered_next(WavesetSynthTriggered *unit, int inNumSamples);
void WavesetSynthTriggered_Dtor(WavesetSynthTriggered *unit);

#endif // WavesetSynthTriggered_H
