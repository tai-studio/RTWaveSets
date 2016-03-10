#include "WsFeatureExtractor.h"

WsFeatureExtractor::WsFeatureExtractor(WsStorage *wsData) : wsData(wsData)
{

}

float WsFeatureExtractor::getFeature(int wsIdx, int featureID)
{
    Waveset* ws = this->wsData->getWaveSet(wsIdx);


    float result;

    if(featureID==0) {
        // WS length in seconds
        result = (float) ws->getLength() / 44100.0;
    } else if(featureID==1) {
        // WS rms 0..1
        result = ws->getRMS();
    } else {
        // unknown featureID
        result = -1;
    }

    delete ws;

    return result;
}

