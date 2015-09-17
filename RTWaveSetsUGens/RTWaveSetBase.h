#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "SC_PlugIn.h"
#include "SoundRingBuffer.h"


#ifdef RTWaveSet_DEBUG
    #define printf_debug(fmt,...) printf(fmt,...)
#else
    #define printf_debug(fmt,...)
#endif

#define printf_warn(fmt,...) printf(fmt,...)

struct RTWaveSetBase : public Unit {

    /** Ringbuffer for Input Audio */
    SoundRingBuffer *audioBuf;

    /** Ringbuffer for found ZeroCrossings */
    SoundRingBuffer *xingsBuf;

};

#endif // RTWAVESETBASE_H
