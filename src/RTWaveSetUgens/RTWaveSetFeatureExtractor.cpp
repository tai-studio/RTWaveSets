#include "RTWaveSetFeatureExtractor.h"

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWaveSetFeatureExtractor_Ctor(RTWaveSetFeatureExtractor *unit)
{
    RTWaveSetBase_Ctor(unit);
    new(&unit->wsExtractor) WsFeatureExtractor(&unit->wsData);

    SETCALC(RTWaveSetFeatureExtractor_next);

    RTWaveSetFeatureExtractor_next(unit, 1);
}

/**
 * @brief Processing.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetFeatureExtractor_next(RTWaveSetFeatureExtractor *unit, int inNumSamples)
{
    float *out = OUT(0);
    float inFeatureID = IN0(2);
    int featureID = (int) inFeatureID;
    float *inIdx = IN(3);

    for (int i=0; i<inNumSamples; ++i)
    {
        int idx = (int) inIdx[i];
        float result = unit->wsExtractor.getFeature(idx,featureID);

        out[i] = result;
    }
}

/**
 * @brief UGen Destructor.
 * @param unit
 */

void RTWaveSetFeatureExtractor_Dtor(RTWaveSetFeatureExtractor *unit)
{

}
