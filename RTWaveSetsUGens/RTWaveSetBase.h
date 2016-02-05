#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "SC_PlugIn.h"
#include "RingBuffer.h"
#include "WaveSet.h"

//#define RTWaveSet_DEBUG

#ifdef RTWaveSet_DEBUG
    #define printf_debug printf
#else
    #define printf_debug(...)
#endif

#define printf_warn printf

typedef RingBuffer<WaveSet> WaveSetRingBuffer;
typedef RingBuffer<float> FloatRingBuffer;

struct RTWaveSetBase : public Unit {

    /** Ringbuffer for Input Audio */
    FloatRingBuffer *audioBuf;

    /** Ringbuffer for found ZeroCrossings */
    WaveSetRingBuffer *wsBuf;

};

void RTWaveSetBase_Ctor(RTWaveSetBase* unit);
SndBuf* RTWaveSetBase_getSndBuf(float fbufnum, Unit* unit);
template <typename T>
RingBuffer<T>* RTWaveSetBase_createRingBufferInBuffer(float fbufnum, Unit *unit);

#endif // RTWAVESETBASE_H
