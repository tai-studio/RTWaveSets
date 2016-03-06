#ifndef WSANALYSIS_H
#define WSANALYSIS_H

#include "WsStorage.h"
#include "WaveSetBuilder.h"


class WsAnalysis : public WsObject
{
private:
    WsStorage* wsData;
    WaveSetBuilder* wsBuilder;
    float lastIn;

public:
    WsAnalysis(WsStorage* wsData);
    ~WsAnalysis();
    void nextInputSample(float val, int minWSLen);
    void reset();
    int getFirstWsIdx();
    int getLastWsIdx();
};

#endif // WSANALYSIS_H
