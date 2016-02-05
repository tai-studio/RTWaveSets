#ifndef RTWAVESETANALYSIS_H
#define RTWAVESETANALYSIS_H

#include "RTWaveSetBase.h"

struct RTWaveSetAnalysis : public RTWaveSetBase  {
    float lastAnalysisOn;
    int minWavesetLength;
    int lastXing;
};

void RTWaveSetAnalysis_Ctor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_next(RTWaveSetAnalysis *unit, int inNumSamples);
void RTWaveSetAnalysis_Dtor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_gotXing(RTWaveSetAnalysis *unit);
float RTWaveSetAnalysis_calcRMS(RTWaveSetAnalysis *unit, int start, int end);

#endif // RTWAVESETANALYSIS_H
