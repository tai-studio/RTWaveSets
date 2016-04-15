#ifndef WavesetGetFeature_H
#define WavesetGetFeature_H

#include "WavesetBase.h"
#include "WavesetProcessing/WsGetFeature.h"

struct WavesetGetFeature : public WavesetBase  {
    WsGetFeature wsExtractor;
};

void WavesetGetFeature_Ctor(WavesetGetFeature *unit);
void WavesetGetFeature_next(WavesetGetFeature *unit, int inNumSamples);
void WavesetGetFeature_Dtor(WavesetGetFeature *unit);

#endif // WavesetGetFeature_H
