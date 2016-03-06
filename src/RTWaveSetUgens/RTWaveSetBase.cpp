#include "RTWaveSetBase.h"
#include "WaveSetStorage/WsStorageDualBuf.h"
#include "WsObject.h"

void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    WsObject::setScWorld(unit->mWorld);

    unit->wsData = new WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}

void RTWaveSetBase_Dtor(RTWaveSetBase *unit)
{
    delete unit->wsData;
}
