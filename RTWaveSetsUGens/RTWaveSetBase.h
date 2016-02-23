#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "SC_PlugIn.h"
#include "RingBuffer.h"
#include "WaveSet.h"
#include "WsStorageDualBuf.h"

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
