#include "RTWaveSetSelector.h"
#include <float.h>

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWaveSetSelector_Ctor(RTWaveSetSelector *unit)
{
    RTWaveSetBase_Ctor(unit);

    SETCALC(RTWaveSetSelector_next);
    unit->searchIdx = -1;
    unit->bestIdx = unit->wsBuf->getFirstPos()+1;
    unit->bestDiff = FLT_MAX;
    unit->desiredLen = -1;
    unit->desiredRMS = -1;
    unit->startSearchIdx = -1;

    // TODO replace fixed weight by a dynamic one, e.g. based on average values
    unit->lenWeight = 1;
    unit->ampWeight = 200;


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
    int inDesiredLen = (int) (inDesiredLenSec * unit->mWorld->mFullRate.mSampleRate)+0.5f; // convert to samples

    // receive input for desired amplitude
    float inDesiredAmp = IN0(3);

    // receive lookBackLimit input
    int inLookBackLimit = (int) IN0(4);

    // update serach paramters
    RTWaveSetSelector_setSearchParams(unit,inDesiredLen,inDesiredAmp, inLookBackLimit);

    // search
    RTWaveSetSelector_findBestIdx(unit);

    // Output
    for (int i=0; i<inNumSamples; ++i)
    {
        out[i]=unit->bestIdx;
    }

}


/**
 * @brief Set the search parameters, restart search if necessary.
 */

void RTWaveSetSelector_setSearchParams(RTWaveSetSelector *unit, float desiredLen, float desiredAmp,int lookBackLimit){

    // find WS idx to start searching depending on lookBackLimit
    int inStartSearchIdx;
    if(lookBackLimit>=0 && lookBackLimit < unit->wsBuf->getLen()) {
        inStartSearchIdx = unit->wsBuf->getLastPos() - lookBackLimit;
    } else {
        inStartSearchIdx = unit->wsBuf->getFirstPos();
    }

    if(unit->searchIdx<inStartSearchIdx) unit->searchIdx = inStartSearchIdx;

    // check if we have to restart Searching
    if(desiredLen != unit->desiredLen
            || desiredAmp != unit->desiredRMS
            || unit->bestIdx < inStartSearchIdx // last result out of lookback range?
            || inStartSearchIdx < unit->startSearchIdx
            || !unit->wsBuf->isInRange(unit->bestIdx) // last result out of xing buffer range?
            || !unit->audioBuf->isInRange(unit->wsBuf->get(unit->bestIdx).start) // out of audio buffer range?
            )
    {
        // restart Searching by resetting variables
        unit->desiredLen = desiredLen;
        unit->desiredRMS = desiredAmp;
        unit->startSearchIdx = inStartSearchIdx;
        unit->searchIdx = inStartSearchIdx;
        unit->bestIdx = unit->searchIdx;
        unit->bestDiff = FLT_MAX;
    }

}

/**
 * @brief Calculate the diff of features.
 */

float RTWaveSetSelector_calcDiff(RTWaveSetSelector *unit, WaveSet ws){
    float diff=0.0;

    if(unit->desiredLen!=-1) {
        float diffLen = unit->lenWeight * abs(unit->desiredLen-ws.getLength());
        diff += diffLen*diffLen;
    }

    if(unit->desiredRMS>=0) {
        float diffRMS = unit->ampWeight * fabs(unit->desiredRMS-ws.amp);
        diff += diffRMS*diffRMS;
    }

    return diff;
}


/**
 * @brief Find the index of the waveset with the smallest diff.
 * @param unit
 */

void RTWaveSetSelector_findBestIdx(RTWaveSetSelector *unit){

    // search for best WS idx
    if(unit->desiredLen<0 && unit->desiredRMS<0)
    {
       unit->bestIdx = unit->wsBuf->getLastPos();
    }
    else
    {
        int oldBestIdx = unit->bestIdx;

        int idx;
        for(idx = unit->searchIdx; idx<=unit->wsBuf->getLastPos(); idx++)
        {
            WaveSet ws = unit->wsBuf->get(idx);

            float diff = RTWaveSetSelector_calcDiff(unit,ws);

            if (diff <= unit->bestDiff)
            {
                unit->bestIdx = idx;
                unit->bestDiff = diff;
            }

        }
        unit->searchIdx = idx;

        if(oldBestIdx != unit->bestIdx) {
            WaveSet ws = unit->wsBuf->get(unit->bestIdx);
            printf_debug("RTWaveSetSelector: bestIdx=%i len=%i, amp=%f\n",unit->bestIdx,ws.getLength(),ws.amp);
        }

    }
}

/**
 * @brief UGen Desstructor.
 * @param unit
 */

void RTWaveSetSelector_Dtor(RTWaveSetSelector *unit)
{

}
