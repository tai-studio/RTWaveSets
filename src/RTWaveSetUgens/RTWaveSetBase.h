#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "WaveSetStorage/RingBuffer.h"
#include "WaveSetStorage/WaveSet.h"
#include "WaveSetStorage/WsStorageDualBuf.h"

//#define RTWaveSet_DEBUG

#ifdef RTWaveSet_DEBUG
    #define printf_debug printf
#else
    #define printf_debug(...)
#endif

#define printf_warn printf

struct RTWaveSetBase : public Unit {
    WsStorageDualBuf wsData;
};

void RTWaveSetBase_Ctor(RTWaveSetBase* unit);

#endif // RTWAVESETBASE_H
