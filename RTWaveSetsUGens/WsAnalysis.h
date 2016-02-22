#ifndef WSANALYSIS_H
#define WSANALYSIS_H

#include "WaveSetData.h"

class WsAnalysis
{
private:
    WaveSetData wsData;
    float lastIn;
    int lastXing;

    void gotXing(int minWSLen);
    float calcRMS(int start, int end);
public:
    WsAnalysis(WaveSetData wsData);
    void nextInputSample(float val, int minWSLen);
    void reset();
    int getFirstWsIdx();
    int getLastWsIdx();
};

#endif // WSANALYSIS_H
