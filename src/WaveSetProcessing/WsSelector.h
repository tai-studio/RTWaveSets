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

    float lenWeight;
    float ampWeight;


    void findBestIdx();
    float calcDiff(Waveset *ws);
    void setSearchParams(int desiredLen, float desiredAmp,int lookBackLimit);
public:
    WsSelector(WsStorage *wsData);
    int findBestIdx(float inDesiredDur, float desiredRMS, float inLookBackLimit);
};

#endif // WSSELECTOR_H
