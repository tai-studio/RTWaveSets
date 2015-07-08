#include "RTWaveSetBase.h"

/**
 * @brief RTWaveSetBase_Ctor Constructor of the RTWaveSet base UGEN.
 * @param unit
 */

void RTWaveSetBase_Ctor(RTWaveSetBase *unit) {
    printf("RTWaveSetBase_Ctor()\n");

    // receive Audio Buffer arg
    //unit->inBuffer = SoundRingBuffer(ZIN0(0),unit);
    //printf("RTWaveSetAnalysis_Ctor: inBuffer (bufnum=%i,len=%i)\n",(int)(ZIN0(0)),unit->inBuffer.getLen());

    // receive Zero Crossing Buffer
    //unit->zeroBuffer = SoundRingBuffer(ZIN0(1),unit);
    //printf("RTWaveSetAnalysis_Ctor: zeroBuffer (bufnum=%i,len=%i)\n",(int)(ZIN0(1)),unit->zeroBuffer.getLen());
}

