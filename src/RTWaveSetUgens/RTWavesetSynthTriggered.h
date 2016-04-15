#ifndef RTWavesetSynthTriggered_H
#define RTWavesetSynthTriggered_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/SynthParallel.h"

#define RTWavesetSynthTriggered_NumIterators (512)

struct RTWavesetSynthTriggered : public RTWavesetBase  {

    SynthParallel wsSynth;

    /** Previous Trigger Input */
    float prevTrig;

};

void RTWavesetSynthTriggered_Ctor(RTWavesetSynthTriggered *unit);
void RTWavesetSynthTriggered_next(RTWavesetSynthTriggered *unit, int inNumSamples);
void RTWavesetSynthTriggered_Dtor(RTWavesetSynthTriggered *unit);

#endif // RTWavesetSynthTriggered_H
