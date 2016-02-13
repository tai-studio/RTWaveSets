#include "RTWaveSetBase.h"


void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    //unit->wsData.audioBuf = WaveSetData::createRingBufferInBuffer<float>(ZIN0(0),unit);//RTWaveSetBase_createRingBufferInBuffer<float>(ZIN0(0),unit);
    //unit->wsData.wsBuf = WaveSetData::createRingBufferInBuffer<WaveSet>((ZIN0(0),unit);
    unit->wsData = WaveSetData(ZIN0(0),ZIN0(1),unit);
}



