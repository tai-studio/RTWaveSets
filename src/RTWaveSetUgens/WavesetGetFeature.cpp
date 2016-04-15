#include "WavesetGetFeature.h"

/**
 * @brief UGen Constructor.
 * @param unit
 */

void WavesetGetFeature_Ctor(WavesetGetFeature *unit)
{
    WavesetBase_Ctor(unit);
    new(&unit->wsExtractor) WsGetFeature(unit->wsData);

    SETCALC(WavesetGetFeature_next);

    WavesetGetFeature_next(unit, 1);
}

/**
 * @brief Processing.
 * @param unit
 * @param inNumSamples
 */

void WavesetGetFeature_next(WavesetGetFeature *unit, int inNumSamples)
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

void WavesetGetFeature_Dtor(WavesetGetFeature *unit)
{

}
