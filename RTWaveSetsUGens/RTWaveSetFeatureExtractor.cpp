#include "RTWaveSetFeatureExtractor.h"

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWaveSetFeatureExtractor_Ctor(RTWaveSetFeatureExtractor *unit)
{
    RTWaveSetBase_Ctor(unit);

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
        float result;

        if(featureID==0) {
            // WS length in seconds
            result = (float) unit->wsBuf->get(idx).getLength() / unit->mWorld->mFullRate.mSampleRate;
        } else if(featureID==1) {
            // WS amplitude 0..1
            result = unit->wsBuf->get(idx).amp;
        } else {
            // unknown featureID
            result = -1;
        }

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
