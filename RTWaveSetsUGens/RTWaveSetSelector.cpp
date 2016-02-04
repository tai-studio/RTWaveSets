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
    // TODO split to several functions

    float *out = OUT(0);

    // receive input for desired length
    float inDesiredLenSec = IN0(2);
    int inDesiredLen = (int) (inDesiredLenSec * unit->mWorld->mFullRate.mSampleRate)+0.5f;
    if(inDesiredLen < 0) inDesiredLen = -1;

    //receive input for desired amplitude
    float inDesiredAmp = IN0(3);

    // check if we have to restart Searching
    if(inDesiredLen != unit->desiredLen
            || inDesiredAmp != unit->desiredRMS
            || !unit->wsBuf->isInRange(unit->bestIdx) // out of xing buffer range?
            || !unit->audioBuf->isInRange(unit->wsBuf->get(unit->bestIdx).start) // out of audio buffer range?
            )
    {
        unit->desiredLen = inDesiredLen;
        unit->desiredRMS = inDesiredAmp;
        unit->searchIdx = unit->wsBuf->getFirstPos();
        unit->bestIdx = unit->searchIdx;
        unit->bestDiff = FLT_MAX;
        printf_debug("RTWaveSetSelector_next() restart Searching (desiredLen %i, desiredAmp %f).\n",unit->desiredLen,unit->desiredRMS);
    }

    // search for best WS idx
    if(unit->desiredLen==-1 && unit->desiredRMS<0)
    {
       unit->bestIdx = unit->wsBuf->getLastPos();
    }
    else
    {
        int oldBestIdx = unit->bestIdx;

        int idx;
        for(idx = unit->searchIdx; idx<unit->wsBuf->getLastPos(); idx++)
        {
            WaveSet ws = unit->wsBuf->get(idx);
            float diff=0.0;

            if(unit->desiredLen!=-1) {
                float diffLen = unit->lenWeight * abs(unit->desiredLen-ws.getLength());
                diff += diffLen*diffLen;
            }

            if(unit->desiredRMS>=0) {
                float diffRMS = unit->ampWeight * fabs(unit->desiredRMS-ws.amp);
                diff += diffRMS*diffRMS;
            }

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

    // Output
    for (int i=0; i<inNumSamples; ++i)
    {
        out[i]=unit->bestIdx;
    }

}

/**
 * @brief UGen Desstructor.
 * @param unit
 */

void RTWaveSetSelector_Dtor(RTWaveSetSelector *unit)
{

}
