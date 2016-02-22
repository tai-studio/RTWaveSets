#ifndef WAVESETDATA_H
#define WAVESETDATA_H

#include "RingBuffer.h"
#include "WaveSet.h"

typedef RingBuffer<WaveSet> WaveSetRingBuffer;
typedef RingBuffer<float> FloatRingBuffer;

class WaveSetData
{
public:

    /** Ringbuffer for Input Audio */
    FloatRingBuffer *audioBuf;

    /** Ringbuffer for Wavesets */
    WaveSetRingBuffer *wsBuf;

    WaveSetData(FloatRingBuffer *audioBuf, WaveSetRingBuffer *wsBuf);
    WaveSetData(float fbufnumAudio, float fbufnumWS, Unit* unit);
    void cleanUp();
    //WaveSetPlay getWaveSetGroup();

    template <typename T>
    static RingBuffer<T>* createRingBufferInBuffer(float fbufnum, Unit *unit);
    static SndBuf* RTWaveSetBase_getSndBuf(float fbufnum, Unit* unit);
};

#endif // WAVESETDATA_H
