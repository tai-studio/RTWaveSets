#ifndef WSFEATUREEXTRACTOR_H
#define WSFEATUREEXTRACTOR_H

#include "WsStorage.h"

class WsFeatureExtractor : public WsObject
{
private:
    WsStorage* wsData;
public:
    WsFeatureExtractor(WsStorage* wsData);
    float getFeature(int wsIdx, int featureID);
};

#endif // WSFEATUREEXTRACTOR_H
