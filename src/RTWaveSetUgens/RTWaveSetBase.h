#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "WavesetStorage/RingBuffer.h"
#include "WavesetStorage/WsStorageDualBuf.h"


struct RTWavesetBase : public Unit {

    /** Pointer with abstract base type to WsStorage instance */
    WsStorage *wsData;

};

void RTWavesetBase_Ctor(RTWavesetBase* unit);
void RTWavesetBase_Dtor(RTWavesetBase* unit);

#endif // RTWAVESETBASE_H
