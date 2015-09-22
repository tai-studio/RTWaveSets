#include "RTWaveSetSelector.h"

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWaveSetSelector_Ctor(RTWaveSetSelector *unit)
{
    unit->audioBuf = FloatRingBuffer::getFromBuffer(ZIN0(0),unit);
    unit->wsBuf = WaveSetRingBuffer::getFromBuffer(ZIN0(1),unit);
    //unit->xingLenBuffer = RingBufferBuffer(unit->xingLenData,RTWaveSetSelector_xingLenBufferLen);

    SETCALC(RTWaveSetSelector_next);
    unit->searchIdx = -1;
    unit->bestIdx = unit->wsBuf->getFirstPos()+1;
    unit->bestDiff = 99999.0;
    unit->desiredLen = -1;
    unit->desiredAmp = -1;

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
    float inDesiredLenMs = IN0(2);
    int inDesiredLen = (int) (inDesiredLenMs * unit->mRate->mSampleRate / 1000.0)+0.5f;
    if(inDesiredLen < 0) inDesiredLen = -1;

    //receive input for desired amplitude
    float inDesiredAmp = IN0(3);

    // check if we have to restart Searching
    if(inDesiredLen != unit->desiredLen
            || inDesiredAmp != unit->desiredAmp
            || !unit->wsBuf->isInRange(unit->bestIdx) // out of xing buffer range?
            || !unit->audioBuf->isInRange(unit->wsBuf->get(unit->bestIdx).start) // out of audio buffer range?
            )
    {
        unit->desiredLen = inDesiredLen;
        unit->desiredAmp = inDesiredAmp;
        unit->searchIdx = unit->wsBuf->getFirstPos();
        unit->bestIdx = unit->searchIdx;
        unit->bestDiff = 9999999.0;
        printf_debug("RTWaveSetSelector_next() restart Searching (desiredLen %i, desiredAmp %f).\n",unit->desiredLen,unit->desiredAmp);
    }

    // search for best WS idx
    if(unit->desiredLen==-1 && unit->desiredAmp<0)
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
                diff+=unit->lenWeight * abs(unit->desiredLen-ws.getLength());
            }

            if(unit->desiredAmp>=0) {
                diff+=unit->ampWeight * fabs(unit->desiredAmp-ws.amp);
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
        // TODO implement selection rules
    }

}

/**
 * @brief UGen Desstructor.
 * @param unit
 */

void RTWaveSetSelector_Dtor(RTWaveSetSelector *unit)
{

}
