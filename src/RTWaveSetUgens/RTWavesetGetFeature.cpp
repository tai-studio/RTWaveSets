#include "RTWavesetGetFeature.h"

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWavesetGetFeature_Ctor(RTWavesetGetFeature *unit)
{
    RTWavesetBase_Ctor(unit);
    new(&unit->wsExtractor) WsGetFeature(unit->wsData);

    SETCALC(RTWavesetGetFeature_next);

    RTWavesetGetFeature_next(unit, 1);
}

/**
 * @brief Processing.
 * @param unit
 * @param inNumSamples
 */

void RTWavesetGetFeature_next(RTWavesetGetFeature *unit, int inNumSamples)
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

void RTWavesetGetFeature_Dtor(RTWavesetGetFeature *unit)
{

}
