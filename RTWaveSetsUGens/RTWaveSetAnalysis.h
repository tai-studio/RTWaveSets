#ifndef RTWAVESETANALYSIS_H
#define RTWAVESETANALYSIS_H

#include "RTWaveSetBase.h"

// TODO make length limits settable from SC
static const int RTWaveSetAnalysis_minWavesetLength = (int) (0.5 * 44.100); // 0.5 ms
// static const int RTWaveSetAnalysis_maxWavesetLength = (int) (500.0 * 44.100); // 500 ms // TODO implement max Length

struct RTWaveSetAnalysis : public RTWaveSetBase  {
    bool checkWSlen;
};

void RTWaveSetAnalysis_Ctor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_next(RTWaveSetAnalysis *unit, int inNumSamples);
void RTWaveSetAnalysis_Dtor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_gotXing(RTWaveSetAnalysis *unit);

#endif // RTWAVESETANALYSIS_H
