#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "WavesetStorage/RingBuffer.h"
#include "WavesetStorage/WsStorageDualBuf.h"


struct WavesetBase : public Unit {

    /** Pointer with abstract base type to WsStorage instance */
    WsStorage *wsData;

};

void WavesetBase_Ctor(WavesetBase* unit);
void WavesetBase_Dtor(WavesetBase* unit);

#endif // RTWAVESETBASE_H
