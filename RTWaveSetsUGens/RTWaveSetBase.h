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

class WaveSet {
public:
    WaveSet(int start, int end){
        this->start = start;
        this->end = end;
    }
    int getLenth() { return end-start; }
    int start;
    int end;
};

typedef RingBuffer<WaveSet> WaveSetRingBuffer;
typedef RingBuffer<float> FloatRingBuffer;

struct RTWaveSetBase : public Unit {

    /** Ringbuffer for Input Audio */
    FloatRingBuffer *audioBuf;

    /** Ringbuffer for found ZeroCrossings */
    WaveSetRingBuffer *wsBuf;

};

#endif // RTWAVESETBASE_H
