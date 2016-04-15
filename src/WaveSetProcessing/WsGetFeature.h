#ifndef WSFEATUREEXTRACTOR_H
#define WSFEATUREEXTRACTOR_H

#include "WsStorage.h"

class WsGetFeature : public ScObject
{
private:
    WsStorage* wsData;
public:
    WsGetFeature(WsStorage* wsData);
    float getFeature(int wsIdx, int featureID);
};

#endif // WSFEATUREEXTRACTOR_H
