#ifndef RTWAVESETANALYSIS_H
#define RTWAVESETANALYSIS_H

#include "RTWaveSetBase.h"
#include "WaveSetProcessing/WsAnalysis.h"

struct RTWaveSetAnalysis : public RTWaveSetBase  {
    WsAnalysis wsAnalysis;

};

void RTWaveSetAnalysis_Ctor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_next(RTWaveSetAnalysis *unit, int inNumSamples);
void RTWaveSetAnalysis_Dtor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_gotXing(RTWaveSetAnalysis *unit);
float RTWaveSetAnalysis_calcRMS(RTWaveSetAnalysis *unit, int start, int end);

#endif // RTWAVESETANALYSIS_H
