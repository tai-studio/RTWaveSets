#ifndef RTWavesetPlayerTriggered_H
#define RTWavesetPlayerTriggered_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/SynthParallel.h"

#define RTWavesetPlayerTriggered_NumIterators (512)

struct RTWavesetPlayerTriggered : public RTWavesetBase  {

    SynthParallel wsSynth;

    /** Previous Trigger Input */
    float prevTrig;

};

void RTWavesetPlayerTriggered_Ctor(RTWavesetPlayerTriggered *unit);
void RTWavesetPlayerTriggered_next(RTWavesetPlayerTriggered *unit, int inNumSamples);
void RTWavesetPlayerTriggered_Dtor(RTWavesetPlayerTriggered *unit);

#endif // RTWavesetPlayerTriggered_H
