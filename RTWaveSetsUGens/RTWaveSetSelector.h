#ifndef RTWAVESETSELECTOR_H
#define RTWAVESETSELECTOR_H

#include "RTWaveSetBase.h"

struct RTWaveSetSelector : public RTWaveSetBase  {

    int searchIdx;
    float bestDiff;
    int bestIdx;
    int desiredLen;
    float desiredRMS;

    float lenWeight;
    float ampWeight;
};

void RTWaveSetSelector_Ctor(RTWaveSetSelector *unit);
void RTWaveSetSelector_next(RTWaveSetSelector *unit, int inNumSamples);
void RTWaveSetSelector_Dtor(RTWaveSetSelector *unit);

#endif // RTWAVESETSELECTOR_H
