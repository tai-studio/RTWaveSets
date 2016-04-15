#include "WavesetBase.h"
#include "WavesetStorage/WsStorageDualBuf.h"
#include "ScObject.h"

void WavesetBase_Ctor(WavesetBase *unit)
{
    ScObject::setScWorld(unit->mWorld);

    unit->wsData = new WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}

void WavesetBase_Dtor(WavesetBase *unit)
{
    delete unit->wsData;
}
