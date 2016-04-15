#include "WsFeatureExtractor.h"

WsFeatureExtractor::WsFeatureExtractor(WsStorage *wsData) : wsData(wsData)
{

}

float WsFeatureExtractor::getFeature(int wsIdx, int featureID)
{
    Waveset* ws = this->wsData->getWaveset(wsIdx);


    float result;

    if(featureID==0) {
        // WS duration in seconds
        result = ws->getMetaData().dur;
    } else if(featureID==1) {
        // WS rms 0..1
        result = ws->getMetaData().rms;
    } else if(featureID==2) {
        // WS peaks
        result = ws->getMetaData().peaks;
    } else {
        // unknown featureID
        result = -1;
    }

    delete ws;

    return result;
}
