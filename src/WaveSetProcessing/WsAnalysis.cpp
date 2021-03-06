#include "WsAnalysis.h"

/**
 * @brief Constructur, just set the wsData variable.
 * @param wsData
 */

WsAnalysis::WsAnalysis(WsStorage *wsData)
{
    this->wsData = wsData;
    this->wsBuilder = this->wsData->createWavesetBuilder();
    reset();
}

/**
 * @brief WsAnalysis::~WsAnalysis
 */

WsAnalysis::~WsAnalysis()
{
    delete this->wsBuilder;
}

/**
 * @brief Reset the running analysis.
 */

void WsAnalysis::reset()
{
    this->wsBuilder->startNewWaveset();
    this->lastIn = NAN;
}

/**
 * @brief receive Audio Input.
 * @param audioIn
 * @param minWSLen minimal waveset length in samples
 */

void WsAnalysis::nextInputSample(float audioIn, int minWSLen)
{
    this->wsBuilder->addAudio(audioIn);

    // look for a -/+ zero crossing
    if(this->lastIn <= 0.0 && audioIn > 0.0)
    {
        // get WS Length
        int len = wsBuilder->getRunningLegnth();

        // Perform actions depending on WS Length
        if(len>=minWSLen)
        {
            // long enouph, save it!
            wsBuilder->saveAndStartNew();
        }
        else if(len<0)
        {
            // no WS started so far, start a new one!
            wsBuilder->startNewWaveset();
        }
    }

    this->lastIn = audioIn;
}

/**
 * @brief Get the idx of the newes waveset in the storage.
 * @return
 */

int WsAnalysis::getFirstWsIdx()
{
    return wsData->getFirstWsIdx();
}

/**
 * @brief Get the idx of the oldest waveset in the storage.
 * @return
 */

int WsAnalysis::getLastWsIdx()
{
   return wsData->getLastWsIdx();
}
