#ifndef WSANALYSIS_H
#define WSANALYSIS_H

#include "WsStorageDualBuf.h"
#include "WaveSetBuilderDualBuf.h"


class WsAnalysis
{
private:
    WsStorageDualBuf* wsData;
    WaveSetBuilder* wsBuilder;
    float lastIn;

public:
    WsAnalysis(WsStorageDualBuf* wsData);
    void nextInputSample(float val, int minWSLen);
    void reset();
    int getFirstWsIdx();
    int getLastWsIdx();
};

#endif // WSANALYSIS_H
