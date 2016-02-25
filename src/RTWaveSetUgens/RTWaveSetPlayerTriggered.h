#ifndef RTWaveSetPlayerTriggered_H
#define RTWaveSetPlayerTriggered_H

#include "RTWaveSetBase.h"
#include "WaveSetProcessing/SynthParallel.h"

#define RTWaveSetPlayerTriggered_NumIterators (512)

struct RTWaveSetPlayerTriggered : public RTWaveSetBase  {

    SynthParallel wsSynth;

    /** Previous Trigger Input */
    float prevTrig;

};

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit);
void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples);
void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit);

#endif // RTWaveSetPlayerTriggered_H
