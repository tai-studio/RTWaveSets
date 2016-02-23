#include "RTWaveSetBase.h"


void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    //unit->wsData.audioBuf = WsStorageDualBuf::createRingBufferInBuffer<float>(ZIN0(0),unit);//RTWaveSetBase_createRingBufferInBuffer<float>(ZIN0(0),unit);
    //unit->wsData.wsBuf = WsStorageDualBuf::createRingBufferInBuffer<WaveSet>((ZIN0(0),unit);
    unit->wsData = WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}



