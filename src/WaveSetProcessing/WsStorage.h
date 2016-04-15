#ifndef WSSTORAGE_H
#define WSSTORAGE_H

#include "WavesetStorage/WavesetDualBuf.h"
#include "WavesetBuilder.h"

class AudioPiece;

class WsStorage : public ScObject
{
public:
    virtual ~WsStorage(){}
    virtual Waveset* getWaveset(int idx) = 0; // TODO use abstract base type
    virtual int getFirstWsIdx() = 0;
    virtual int getLastWsIdx() = 0;
    virtual int getNumWsInStorage() = 0;
    virtual int getMaxWsCapacity() = 0;
    virtual int isValidWsIdx(int idx) = 0;
    virtual WavesetBuilder* createWavesetBuilder() = 0;
    virtual AudioPiece* createGroup(int wsIdx, int groupSize) = 0;
};

#endif // WSSTORAGE_H
