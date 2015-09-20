#include "RTWaveSetSelector.h"

/**
 * @brief UGen Constructor.
 * @param unit
 */

void RTWaveSetSelector_Ctor(RTWaveSetSelector *unit)
{
    unit->audioBuf = SoundRingBuffer::getFromBuffer(ZIN0(0),unit);
    unit->xingsBuf = SoundRingBuffer::getFromBuffer(ZIN0(1),unit);
    //unit->xingLenBuffer = SoundRingBuffer(unit->xingLenData,RTWaveSetSelector_xingLenBufferLen);

    SETCALC(RTWaveSetSelector_next);
    unit->searchIdx = -1;
    unit->bestIdx = unit->xingsBuf->getFirstPos()+1;
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
    int inDesiredLen = (int) IN0(2);

    // check if we have to restart Searching
    if(inDesiredLen != unit->desiredLen
            || !unit->xingsBuf->isInRange(unit->bestIdx) // out of xing buffer range?
            || !unit->audioBuf->isInRange(unit->xingsBuf->get(unit->bestIdx)) // out of audio buffer range?
            )
    {
        unit->desiredLen = inDesiredLen;
        unit->searchIdx = unit->xingsBuf->getFirstPos()+1;
        unit->bestIdx = unit->searchIdx;
        unit->bestLen = INT16_MAX;
        printf_debug("RTWaveSetSelector_next() restart Searching (desiredLen %i).\n",inDesiredLen);
    }

    // search for best WS idx
    if(unit->desiredLen==-1)
    {
       unit->bestIdx = unit->xingsBuf->getLastPos();
    }
    else
    {
        int oldBestIdx = unit->bestIdx;

        int idx;
        for(idx = unit->searchIdx; idx<unit->xingsBuf->getLastPos(); idx++)
        {
            int len = unit->xingsBuf->get(idx) - unit->xingsBuf->get(idx-1);
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
