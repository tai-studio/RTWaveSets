#ifndef WSSELECTOR_H
#define WSSELECTOR_H

#include "WsStorage.h"

class WsSelector : public ScObject
{
private:
    WsStorage* wsData;

    int startSearchIdx;
    int searchIdx;
    float bestDiff;
    int bestIdx;
    int desiredLen;
    float desiredRMS;
    int desiredPeaks;

    float lenWeight;
    float ampWeight;
    float peaksWeight;

    void findBestIdx();
    float calcDiff(Waveset *ws);
    void setSearchParams(int desiredLen, float desiredAmp, int desiredPeaks, int lookBackLimit);
public:
    WsSelector(WsStorage *wsData);
    int findBestIdx(float inDesiredDur, float desiredRMS, int desiredPeaks, float lookBackLimit);
};

#endif // WSSELECTOR_H
