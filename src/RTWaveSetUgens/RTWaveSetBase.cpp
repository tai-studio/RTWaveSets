#include "RTWaveSetBase.h"
#include "WaveSetStorage/WsStorageDualBuf.h"
#include "ScObject.h"

void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    ScObject::setScWorld(unit->mWorld);

    unit->wsData = new WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}

void RTWaveSetBase_Dtor(RTWaveSetBase *unit)
{
    delete unit->wsData;
}
