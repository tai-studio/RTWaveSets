#ifndef RTWAVESETSELECTOR_H
#define RTWAVESETSELECTOR_H

#include "WavesetBase.h"
#include "WavesetProcessing/WsSelector.h"

struct WavesetSelector : public WavesetBase  {

    WsSelector wsSelector;
};

void WavesetSelector_Ctor(WavesetSelector *unit);
void WavesetSelector_next(WavesetSelector *unit, int inNumSamples);
void WavesetSelector_Dtor(WavesetSelector *unit);

#endif // RTWAVESETSELECTOR_H
