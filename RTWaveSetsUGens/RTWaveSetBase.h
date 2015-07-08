#ifndef RTWAVESETBASE_H
#define RTWAVESETBASE_H

#include "SC_PlugIn.h"
#include "soundringbuffer.h"

struct RTWaveSetBase : public Unit {
    /** Ringbuffer for Input Audio */
    SoundRingBuffer inBuffer;

    /** Ringbuffer for found ZeroCrossings */
    SoundRingBuffer zeroBuffer;
};

void RTWaveSetBase_Ctor(RTWaveSetBase *unit);

#endif // RTWAVESETBASE_H
