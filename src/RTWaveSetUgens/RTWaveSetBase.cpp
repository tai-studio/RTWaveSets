#include "RTWaveSetBase.h"


void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    new (&unit->wsData) WsStorageDualBuf(ZIN0(0),ZIN0(1),unit);
}



