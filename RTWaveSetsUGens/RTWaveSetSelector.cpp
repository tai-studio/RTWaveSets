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
    unit->bestLen = INT16_MAX;
    unit->desiredLen = -1;
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

    // check if we have to restart Searching
    if(inDesiredLen != unit->desiredLen
            || !unit->wsBuf->isInRange(unit->bestIdx) // out of xing buffer range?
            || !unit->audioBuf->isInRange(unit->wsBuf->get(unit->bestIdx).start) // out of audio buffer range?
            )
    {
        unit->desiredLen = inDesiredLen;
        unit->searchIdx = unit->wsBuf->getFirstPos();
        unit->bestIdx = unit->searchIdx;
        unit->bestLen = INT16_MAX;
        printf_debug("RTWaveSetSelector_next() restart Searching (desiredLen %i).\n",inDesiredLen);
    }

    // search for best WS idx
    if(unit->desiredLen==-1)
    {
       unit->bestIdx = unit->wsBuf->getLastPos();
    }
    else
    {
        int oldBestIdx = unit->bestIdx;

        int idx;
        for(idx = unit->searchIdx; idx<unit->wsBuf->getLastPos(); idx++)
        {
            int len = unit->wsBuf->get(idx).getLenth();
            if (abs(unit->desiredLen-len) <= abs(unit->desiredLen-unit->bestLen))
            {
                unit->bestIdx = idx;
                unit->bestLen = len;
            }
        }
        unit->searchIdx = idx;

        if(oldBestIdx != unit->bestIdx) {
            printf_debug("RTWaveSetSelector: bestLen=%i, bestIdx=%i\n",unit->bestLen,unit->bestIdx);
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
