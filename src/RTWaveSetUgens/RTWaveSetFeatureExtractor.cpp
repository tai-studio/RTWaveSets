#include "RTWavesetFeatureExtractor.h"

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWavesetFeatureExtractor_Ctor(RTWavesetFeatureExtractor *unit)
{
    RTWavesetBase_Ctor(unit);
    new(&unit->wsExtractor) WsFeatureExtractor(unit->wsData);

    SETCALC(RTWavesetFeatureExtractor_next);

    RTWavesetFeatureExtractor_next(unit, 1);
}

/**
 * @brief Processing.
 * @param unit
 * @param inNumSamples
 */

void RTWavesetFeatureExtractor_next(RTWavesetFeatureExtractor *unit, int inNumSamples)
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

void RTWavesetFeatureExtractor_Dtor(RTWavesetFeatureExtractor *unit)
{

}
