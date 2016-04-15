#ifndef RTWAVESETANALYSIS_H
#define RTWAVESETANALYSIS_H

#include "WavesetBase.h"
#include "WavesetProcessing/WsAnalysis.h"
#include "ScObject.h"

struct WavesetAnalysis : public WavesetBase  {
    WsAnalysis wsAnalysis;
};

void WavesetAnalysis_Ctor(WavesetAnalysis *unit);
void WavesetAnalysis_next(WavesetAnalysis *unit, int inNumSamples);
void WavesetAnalysis_Dtor(WavesetAnalysis *unit);

#endif // RTWAVESETANALYSIS_H
