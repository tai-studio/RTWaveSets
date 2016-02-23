#ifndef WSANALYSIS_H
#define WSANALYSIS_H

#include "WsStorageDualBuf.h"
#include "WaveSetBuilderDualBuf.h"


class WsAnalysis
{
private:
    WsStorageDualBuf* wsData;

    WaveSetBuilderDualBuf wsBuilder;

    float lastIn;

    //int lastXing;
    //void gotXing(int minWSLen);
    //float calcRMS(int start, int end);

public:
    WsAnalysis(WsStorageDualBuf* wsData);
    void nextInputSample(float val, int minWSLen);
    void reset();
    int getFirstWsIdx();
    int getLastWsIdx();
};

#endif // WSANALYSIS_H
