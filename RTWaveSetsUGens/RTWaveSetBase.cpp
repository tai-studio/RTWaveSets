#include "RTWaveSetBase.h"


void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    unit->audioBuf = FloatRingBuffer::getFromBuffer(ZIN0(0),unit);
    unit->wsBuf = WaveSetRingBuffer::getFromBuffer(ZIN0(1),unit);
}
