#ifndef RTWaveSetFeatureExtractor_H
#define RTWaveSetFeatureExtractor_H

#include "RTWaveSetBase.h"
#include "WaveSetProcessing/WsFeatureExtractor.h"

struct RTWaveSetFeatureExtractor : public RTWaveSetBase  {
    WsFeatureExtractor wsExtractor;
};

void RTWaveSetFeatureExtractor_Ctor(RTWaveSetFeatureExtractor *unit);
void RTWaveSetFeatureExtractor_next(RTWaveSetFeatureExtractor *unit, int inNumSamples);
void RTWaveSetFeatureExtractor_Dtor(RTWaveSetFeatureExtractor *unit);

#endif // RTWaveSetFeatureExtractor_H
