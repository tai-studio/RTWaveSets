#include "RTWaveSetBase.h"
#include "WaveSetStorage/WsStorageDualBuf.h"
#include "WsObject.h"

void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    WsObject::setScWorld(unit->mWorld);

    unit->wsData = new (&unit->wsData_) WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}


void RTWaveSetBase_Dtor(RTWaveSetBase *unit)
{
    unit->wsData->~WsStorage();
}
