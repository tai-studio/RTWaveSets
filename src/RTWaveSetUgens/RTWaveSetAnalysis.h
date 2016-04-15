#ifndef RTWAVESETANALYSIS_H
#define RTWAVESETANALYSIS_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/WsAnalysis.h"
#include "ScObject.h"

struct RTWavesetAnalysis : public RTWavesetBase  {
    WsAnalysis wsAnalysis;
};

void RTWavesetAnalysis_Ctor(RTWavesetAnalysis *unit);
void RTWavesetAnalysis_next(RTWavesetAnalysis *unit, int inNumSamples);
void RTWavesetAnalysis_Dtor(RTWavesetAnalysis *unit);

#endif // RTWAVESETANALYSIS_H
