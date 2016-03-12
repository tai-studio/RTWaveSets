#include "WaveSetBuilderDualBuf.h"
#include "ScFFT.h"
#include <complex.h>

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
    wsData->cleanUp();
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

        WaveSetDualBuf ws(wsData,startPos,endPos);
        ws.calcMetaData();

        wsData->wsBuf->put(ws.data);
    }

    this->startNewWaveSet();
}

