#ifndef RTWavesetGetFeature_H
#define RTWavesetGetFeature_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/WsGetFeature.h"

struct RTWavesetGetFeature : public RTWavesetBase  {
    WsGetFeature wsExtractor;
};

void RTWavesetGetFeature_Ctor(RTWavesetGetFeature *unit);
void RTWavesetGetFeature_next(RTWavesetGetFeature *unit, int inNumSamples);
void RTWavesetGetFeature_Dtor(RTWavesetGetFeature *unit);

#endif // RTWavesetGetFeature_H
