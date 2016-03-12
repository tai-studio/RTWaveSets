#ifndef WSSTORAGE_H
#define WSSTORAGE_H

#include "WaveSetStorage/WaveSetDualBuf.h"
#include "WaveSetBuilder.h"

class AudioPiece;

class WsStorage : public ScObject
{
public:
    virtual ~WsStorage(){}
    virtual Waveset* getWaveSet(int idx) = 0; // TODO use abstract base type
    virtual int getFirstWsIdx() = 0;
    virtual int getLastWsIdx() = 0;
    virtual int getNumWsInStorage() = 0;
    virtual int getMaxWsCapacity() = 0;
    virtual int isValidWsIdx(int idx) = 0;
    virtual WaveSetBuilder* createWaveSetBuilder() = 0;
    virtual AudioPiece* createGroup(int wsIdx, int groupSize) = 0;
};

#endif // WSSTORAGE_H
