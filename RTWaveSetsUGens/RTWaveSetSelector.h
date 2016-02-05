#ifndef RTWAVESETSELECTOR_H
#define RTWAVESETSELECTOR_H

#include "RTWaveSetBase.h"

struct RTWaveSetSelector : public RTWaveSetBase  {

    int searchIdx;
    float bestDiff;
    int bestIdx;
    int desiredLen;
    float desiredRMS;

    /**
     * @brief Only search in the x last wavesets. -1 for no limit.
     */
    int lookBackLimit;

    float lenWeight;
    float ampWeight;
};

void RTWaveSetSelector_Ctor(RTWaveSetSelector *unit);
void RTWaveSetSelector_next(RTWaveSetSelector *unit, int inNumSamples);
void RTWaveSetSelector_Dtor(RTWaveSetSelector *unit);

#endif // RTWAVESETSELECTOR_H
