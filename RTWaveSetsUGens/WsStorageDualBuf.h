#ifndef WAVESETDATA_H
#define WAVESETDATA_H

#include "WsStorage.h"
#include "RingBuffer.h"
#include "WaveSet.h"
#include "WaveSetBuilder.h"

typedef RingBuffer<WaveSet> WaveSetRingBuffer;
typedef RingBuffer<float> FloatRingBuffer;

class WsStorageDualBuf : WsStorage
{
public:

    /** Ringbuffer for Input Audio */
    FloatRingBuffer *audioBuf;

    /** Ringbuffer for Wavesets */
    WaveSetRingBuffer *wsBuf;

    WsStorageDualBuf(FloatRingBuffer *audioBuf, WaveSetRingBuffer *wsBuf);
    WsStorageDualBuf(float fbufnumAudio, float fbufnumWS, Unit* unit);
    void cleanUp();
    //WaveSetPlay getWaveSetGroup();

    template <typename T>
    static RingBuffer<T>* createRingBufferInBuffer(float fbufnum, Unit *unit);
    static SndBuf* RTWaveSetBase_getSndBuf(float fbufnum, Unit* unit);

    /** WsStorage Interface Functions */

    virtual WaveSet getWaveSet(int idx){ return wsBuf->get(idx); }
    virtual int getFirsWsIdx(){ return wsBuf->getFirstPos(); }
    virtual int getLastWsIdx(){ return wsBuf->getLastPos(); }
    virtual int isValidWsidx(int idx){ return wsBuf->isInRange(idx); }
    virtual WaveSetBuilder* createWaveSetBuilder();

};

#endif // WAVESETDATA_H
