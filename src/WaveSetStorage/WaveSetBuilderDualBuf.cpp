#include "WavesetBuilderDualBuf.h"
#include "ScFFT.h"
#include <complex.h>

/**
 * @brief Constructor.
 * @param wsData
 */

WavesetBuilderDualBuf::WavesetBuilderDualBuf(WsStorageDualBuf* wsData)
{
    this->wsData = wsData;
    this->startPos = INT32_MAX;
}


/**
 * @brief Start a new waveset, save current audio position.
 */

void WavesetBuilderDualBuf::startNewWaveset()
{
    startPos = wsData->audioBuf->getLastPos();
}


/**
 * @brief WavesetBuilderDualBuf::addAudio
 * @param val
 */

void WavesetBuilderDualBuf::addAudio(float val)
{
    wsData->audioBuf->put(val);
    wsData->cleanUp();
}


/**
 * @brief Get the current length of the currently building waveset.
 * @return length of the WS or -1 if there is no valid WS started.
 */

int WavesetBuilderDualBuf::getRunningLegnth()
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

void WavesetBuilderDualBuf::saveAndStartNew()
{

    if(wsData->audioBuf->isInRange(startPos)){
        int endPos = wsData->audioBuf->getLastPos();

        WavesetDualBuf ws(wsData,startPos,endPos);
        ws.calcMetaData();

        wsData->wsBuf->put(ws.data);
    }

    this->startNewWaveset();
}

