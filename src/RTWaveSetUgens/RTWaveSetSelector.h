#ifndef RTWAVESETSELECTOR_H
#define RTWAVESETSELECTOR_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/WsSelector.h"

struct RTWavesetSelector : public RTWavesetBase  {

    WsSelector wsSelector;
};

void RTWavesetSelector_Ctor(RTWavesetSelector *unit);
void RTWavesetSelector_next(RTWavesetSelector *unit, int inNumSamples);
void RTWavesetSelector_Dtor(RTWavesetSelector *unit);

#endif // RTWAVESETSELECTOR_H
