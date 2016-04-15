#ifndef WSANALYSIS_H
#define WSANALYSIS_H

#include "WsStorage.h"
#include "WavesetBuilder.h"


class WsAnalysis : public ScObject
{
private:
    WsStorage* wsData;
    WavesetBuilder* wsBuilder;
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
