#ifndef WSSTORAGE_H
#define WSSTORAGE_H

#include "WaveSet.h"
#include "WaveSetBuilder.h"

class WsStorage
{
public:
    virtual WaveSet getWaveSet(int idx) = 0;
    virtual int getFirsWsIdx()=0;
    virtual int getLastWsIdx()=0;
    virtual int isValidWsidx(int idx)=0;
    virtual WaveSetBuilder* createWaveSetBuilder()=0;
};

#endif // WSSTORAGE_H
