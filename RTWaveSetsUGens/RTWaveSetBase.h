#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "SC_PlugIn.h"
#include "RingBuffer.h"
#include "WaveSet.h"
#include "WaveSetData.h"

//#define RTWaveSet_DEBUG

#ifdef RTWaveSet_DEBUG
    #define printf_debug printf
#else
    #define printf_debug(...)
#endif

#define printf_warn printf

struct RTWaveSetBase : public Unit {
    WaveSetData wsData;
};

void RTWaveSetBase_Ctor(RTWaveSetBase* unit);

#endif // RTWAVESETBASE_H
