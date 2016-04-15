#ifndef WAVESETDATA_H
#define WAVESETDATA_H

#include "WavesetProcessing/WsStorage.h"
#include "RingBuffer.h"
#include "WavesetDualBuf.h"
#include "WavesetProcessing/WavesetBuilder.h"

typedef RingBuffer<WavesetDualBuf::Data> WavesetRingBuffer;
typedef RingBuffer<float> FloatRingBuffer;

class WsStorageDualBuf : public WsStorage
{
public:

    /** Ringbuffer for Input Audio */
    FloatRingBuffer *audioBuf;

    /** Ringbuffer for Wavesets */
    WavesetRingBuffer *wsBuf;

    WsStorageDualBuf(FloatRingBuffer *audioBuf, WavesetRingBuffer *wsBuf);
    WsStorageDualBuf(float fbufnumAudio, float fbufnumWS, Unit* unit);
    void cleanUp();

    template <typename T>
    static RingBuffer<T>* createRingBufferInBuffer(float fbufnum, Unit *unit);
    static SndBuf* WavesetBase_getSndBuf(float fbufnum, Unit* unit);

    /** WsStorage Interface Functions */

    /**
     * @brief get a waveset at given position. its allocated dynamic and sould be freed using delete
     * @param idx
     * @return
     */

    virtual Waveset* getWaveset(int idx){ return new WavesetDualBuf(this,wsBuf->get(idx)); }
    virtual int getFirstWsIdx(){ return wsBuf->getFirstPos(); }
    virtual int getLastWsIdx(){ return wsBuf->getLastPos(); }
    virtual int isValidWsIdx(int idx){ return wsBuf->isInRange(idx); }
    virtual int getNumWsInStorage(){return wsBuf->getLen(); }
    virtual int getMaxWsCapacity(){ return wsBuf->getSize(); }
    virtual WavesetBuilder* createWavesetBuilder();
    virtual AudioPiece* createGroup(int wsIdx, int groupSize);
};

#endif // WAVESETDATA_H
