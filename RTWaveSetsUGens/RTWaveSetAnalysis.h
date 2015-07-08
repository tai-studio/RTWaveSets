#ifndef RTWAVESETANALYSIS_H
#define RTWAVESETANALYSIS_H

#include "RTWaveSetBase.h"

struct RTWaveSetAnalysis : public RTWaveSetBase  {

};

void RTWaveSetAnalysis_Ctor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_next(RTWaveSetAnalysis *unit, int inNumSamples);
void RTWaveSetAnalysis_Dtor(RTWaveSetAnalysis *unit);

#endif // RTWAVESETANALYSIS_H
