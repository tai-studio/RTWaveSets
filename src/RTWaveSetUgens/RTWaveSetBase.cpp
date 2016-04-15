#include "RTWavesetBase.h"
#include "WavesetStorage/WsStorageDualBuf.h"
#include "ScObject.h"

void RTWavesetBase_Ctor(RTWavesetBase *unit)
{
    ScObject::setScWorld(unit->mWorld);

    unit->wsData = new WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}

void RTWavesetBase_Dtor(RTWavesetBase *unit)
{
    delete unit->wsData;
}
