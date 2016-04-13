#include "RTWaveSetSelector.h"
#include <float.h>

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWaveSetSelector_Ctor(RTWaveSetSelector *unit)
{
    RTWaveSetBase_Ctor(unit);
    new(&unit->wsSelector) WsSelector(unit->wsData);

    SETCALC(RTWaveSetSelector_next);

    RTWaveSetSelector_next(unit, 1);
}

/**
 * @brief Processing.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetSelector_next(RTWaveSetSelector *unit, int inNumSamples)
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

void RTWaveSetSelector_Dtor(RTWaveSetSelector *unit)
{

}
