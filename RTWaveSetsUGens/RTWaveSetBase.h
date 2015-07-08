#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "SC_PlugIn.h"
#include "soundringbuffer.h"

struct RTWaveSetBase : public Unit {

    /** Ringbuffer for Input Audio */
    SoundRingBuffer *audioBuf;

    /** Ringbuffer for found ZeroCrossings */
    SoundRingBuffer *xingsBuf;

};

#endif // RTWAVESETBASE_H
