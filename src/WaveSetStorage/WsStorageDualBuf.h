#ifndef WAVESETDATA_H
#define WAVESETDATA_H

#include "WaveSetProcessing/WsStorage.h"
#include "RingBuffer.h"
#include "WaveSetDualBuf.h"
#include "WaveSetProcessing/WaveSetBuilder.h"

typedef RingBuffer<WaveSetDualBuf::Data> WaveSetRingBuffer;
typedef RingBuffer<float> FloatRingBuffer;

class WsStorageDualBuf : public WsStorage
{
public:

    /** Ringbuffer for Input Audio */
    FloatRingBuffer *audioBuf;

    /** Ringbuffer for Wavesets */
    WaveSetRingBuffer *wsBuf;

    WsStorageDualBuf(FloatRingBuffer *audioBuf, WaveSetRingBuffer *wsBuf);
    WsStorageDualBuf(float fbufnumAudio, float fbufnumWS, Unit* unit);
    void cleanUp();

    template <typename T>
    static RingBuffer<T>* createRingBufferInBuffer(float fbufnum, Unit *unit);
    static SndBuf* RTWaveSetBase_getSndBuf(float fbufnum, Unit* unit);

    /** WsStorage Interface Functions */

    /**
     * @brief get a waveset at given position. its allocated dynamic and sould be freed using delete
     * @param idx
     * @return
     */

    virtual Waveset* getWaveSet(int idx){ return new WaveSetDualBuf(wsBuf->get(idx)); }
    virtual int getFirstWsIdx(){ return wsBuf->getFirstPos(); }
    virtual int getLastWsIdx(){ return wsBuf->getLastPos(); }
    virtual int isValidWsIdx(int idx){ return wsBuf->isInRange(idx); }
    virtual int getNumWsInStorage(){return wsBuf->getLen(); }
    virtual int getMaxWsCapacity(){ return wsBuf->getSize(); }
    virtual WaveSetBuilder* createWaveSetBuilder();
    virtual AudioPiece* createGroup(int wsIdx, int groupSize);
};

#endif // WAVESETDATA_H
