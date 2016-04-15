#include "RTWavesetSelector.h"
#include <float.h>

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWavesetSelector_Ctor(RTWavesetSelector *unit)
{
    RTWavesetBase_Ctor(unit);
    new(&unit->wsSelector) WsSelector(unit->wsData);

    SETCALC(RTWavesetSelector_next);

    RTWavesetSelector_next(unit, 1);
}

/**
 * @brief Processing.
 * @param unit
 * @param inNumSamples
 */

void RTWavesetSelector_next(RTWavesetSelector *unit, int inNumSamples)
{
    float *out = OUT(0);

    WsMedatData desiredFtrs;

    // receive inputs for desired features
    desiredFtrs.dur = IN0(2);
    desiredFtrs.rms = IN0(3);
    desiredFtrs.peaks = (int) IN0(4);

    // receive lookBackLimit input
    int inLookBackLimit = (int) IN0(5);

    // perform selection
    int result = unit->wsSelector.findBestIdx(desiredFtrs.dur,desiredFtrs.rms,desiredFtrs.peaks,inLookBackLimit);

    // Output
    for (int i=0; i<inNumSamples; ++i)
    {
        out[i]=result;
    }

}


/**
 * @brief UGen Desstructor.
 * @param unit
 */

void RTWavesetSelector_Dtor(RTWavesetSelector *unit)
{

}
