#include "WaveSetBuilderDualBuf.h"

/**
 * @brief Constructor.
 * @param wsData
 */

WaveSetBuilderDualBuf::WaveSetBuilderDualBuf(WsStorageDualBuf* wsData)
{
    this->wsData = wsData;
    this->startPos = INT32_MAX;
}


/**
 * @brief Start a new waveset, save current audio position.
 */

void WaveSetBuilderDualBuf::startNewWaveSet()
{
    startPos = wsData->audioBuf->getLastPos();
}


/**
 * @brief WaveSetBuilderDualBuf::addAudio
 * @param val
 */

void WaveSetBuilderDualBuf::addAudio(float val)
{
    wsData->audioBuf->put(val);
}


/**
 * @brief Get the current length of the currently building waveset.
 * @return length of the WS or -1 if there is no valid WS started.
 */

int WaveSetBuilderDualBuf::getRunningLegnth()
{
    if(wsData->audioBuf->isInRange(startPos)){
        return wsData->audioBuf->getLastPos() - startPos;
    }
    else {
        return -1;
    }
}


/**
 * @brief close the waveset and save it to the storage.
 */

void WaveSetBuilderDualBuf::saveAndStartNew()
{

    if(wsData->audioBuf->isInRange(startPos)){
        int endPos = wsData->audioBuf->getLastPos();
        float rms = calcRMS(startPos,endPos);
        WaveSet ws(startPos,endPos,rms);
        wsData->wsBuf->put(ws);
    }

    this->startNewWaveSet();
}

/**
 * @brief Calculate the RMS of a waveset signal.
 * @param start
 * @param end
 * @return
 */

float WaveSetBuilderDualBuf::calcRMS(int start,int end){
    float rms = 0.0;

    for(int idx=start;idx<end;idx++) // TODO inclusive or exclusive end? also relevant for length, playback
    {
        float val = wsData->audioBuf->get(idx);
        rms += val*val;
    }

    rms = sqrtf(rms / (end-start));
    return rms;
}
