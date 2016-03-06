#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "WaveSetStorage/RingBuffer.h"
#include "WaveSetStorage/WsStorageDualBuf.h"


struct RTWaveSetBase : public Unit {

    /** preserver memory for the wsData instance */
    WsStorageDualBuf wsData_;

    /** Pointer with abstract base type to WsStorage instance */
    WsStorage *wsData;

};

void RTWaveSetBase_Ctor(RTWaveSetBase* unit);
void RTWaveSetBase_Dtor(RTWaveSetBase* unit);

#endif // RTWAVESETBASE_H
