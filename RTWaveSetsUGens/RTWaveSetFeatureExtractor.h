#ifndef RTWaveSetFeatureExtractor_H
#define RTWaveSetFeatureExtractor_H

#include "RTWaveSetBase.h"

struct RTWaveSetFeatureExtractor : public RTWaveSetBase  {


};

void RTWaveSetFeatureExtractor_Ctor(RTWaveSetFeatureExtractor *unit);
void RTWaveSetFeatureExtractor_next(RTWaveSetFeatureExtractor *unit, int inNumSamples);
void RTWaveSetFeatureExtractor_Dtor(RTWaveSetFeatureExtractor *unit);

#endif // RTWaveSetFeatureExtractor_H
