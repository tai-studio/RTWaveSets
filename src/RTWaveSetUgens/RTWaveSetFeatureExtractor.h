#ifndef RTWavesetFeatureExtractor_H
#define RTWavesetFeatureExtractor_H

#include "RTWavesetBase.h"
#include "WavesetProcessing/WsFeatureExtractor.h"

struct RTWavesetFeatureExtractor : public RTWavesetBase  {
    WsFeatureExtractor wsExtractor;
};

void RTWavesetFeatureExtractor_Ctor(RTWavesetFeatureExtractor *unit);
void RTWavesetFeatureExtractor_next(RTWavesetFeatureExtractor *unit, int inNumSamples);
void RTWavesetFeatureExtractor_Dtor(RTWavesetFeatureExtractor *unit);

#endif // RTWavesetFeatureExtractor_H
