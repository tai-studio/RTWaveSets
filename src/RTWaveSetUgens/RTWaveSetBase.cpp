#include "RTWaveSetBase.h"
#include "WaveSetStorage/WsStorageDualBuf.h"

void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    unit->wsData = new (&unit->wsData_) WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}



