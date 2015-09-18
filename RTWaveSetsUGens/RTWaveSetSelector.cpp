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
    unit->searchIdx = 1;
    unit->bestIdx = -1;
    unit->bestLen = INT16_MAX;
    unit->desiredLen = 200;
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

    if(inDesiredLen != unit->desiredLen)
    {
        unit->desiredLen = inDesiredLen;
        unit->searchIdx = 1; // TODO start at first idx of xingBuffer range
        unit->bestIdx = -1;
        unit->bestLen = INT16_MAX;
        printf_debug("RTWaveSetSelector_next() set desiredLen to %i.\n",inDesiredLen);
    }

    // TODO check if bestIdx is still in Buffer range
    int idx;
    for(idx=unit->searchIdx; idx<unit->xingsBuf->getLastPos(); idx++)
    {
        int len = unit->xingsBuf->get(idx) - unit->xingsBuf->get(idx-1);
        if (abs(unit->desiredLen-len) <= abs(unit->desiredLen-unit->bestLen))
        {
            unit->bestIdx = idx;
            unit->bestLen = len;
        }
    }
    unit->searchIdx = idx;

    // calcualte WS lengths if more xings available
    /*while(unit->xingsBuf->getLastPos() > unit->xingLenBuffer.getLastPos() + 1)
    {
        int idx = unit->xingLenBuffer.getLastPos()+1;
        int len = unit->xingsBuf->get(idx) - unit->xingsBuf->get(idx-1);

        unit->xingLenBuffer.put((float) len);
        printf_debug("RTWaveSetSelector_next() WaveSet %i with length %i\n",idx,len);
    }*/

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
