#ifndef WSSTORAGE_H
#define WSSTORAGE_H

#include "WaveSetStorage/WaveSetDualBuf.h"
#include "WaveSetBuilder.h"

class WsStorage
{
public:
    virtual WaveSetDualBuf getWaveSet(int idx) = 0;
    virtual int getFirsWsIdx() = 0;
    virtual int getLastWsIdx() = 0;
    virtual int isValidWsidx(int idx) = 0;
    virtual WaveSetBuilder* createWaveSetBuilder() = 0;
};

#endif // WSSTORAGE_H
