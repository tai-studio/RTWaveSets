#ifndef WSANALYSIS_H
#define WSANALYSIS_H

#include "WsStorage.h"
#include "WaveSetBuilder.h"


class WsAnalysis
{
private:
    WsStorage* wsData; // TODO change to abstract base WsStorage
    WaveSetBuilder* wsBuilder;
    float lastIn;

public:
    WsAnalysis(WsStorage* wsData);
    void nextInputSample(float val, int minWSLen);
    void reset();
    int getFirstWsIdx();
    int getLastWsIdx();
};

#endif // WSANALYSIS_H
