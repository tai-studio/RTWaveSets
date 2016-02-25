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

    // receive input for desired length
    float inDesiredLenSec = IN0(2);

    // receive input for desired amplitude
    float inDesiredRMS = IN0(3);

    // receive lookBackLimit input
    int inLookBackLimit = (int) IN0(4);

    // perform selection
    int result = unit->wsSelector.findBestIdx(inDesiredLenSec,inDesiredRMS,inLookBackLimit);

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
