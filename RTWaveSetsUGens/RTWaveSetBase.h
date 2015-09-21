#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "SC_PlugIn.h"
#include "RingBuffer.h"

//#define RTWaveSet_DEBUG

#ifdef RTWaveSet_DEBUG
    #define printf_debug printf
#else
    #define printf_debug(...)
#endif

#define printf_warn printf

struct RTWaveSetBase : public Unit {

    /** Ringbuffer for Input Audio */
    FloatRingBuffer *audioBuf;

    /** Ringbuffer for found ZeroCrossings */
    FloatRingBuffer *xingsBuf;

};

#endif // RTWAVESETBASE_H
