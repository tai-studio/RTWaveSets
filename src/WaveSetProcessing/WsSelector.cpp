#include "WsSelector.h"
#include "float.h"

WsSelector::WsSelector(WsStorage *wsData) : wsData(wsData)
{
    this->searchIdx = -1;
    this->bestIdx = this->wsData->getFirstWsIdx()+1;
    this->bestDiff = FLT_MAX;
    this->desiredLen = -1;
    this->desiredRMS = -1;
    this->desiredPeaks = -1;
    this->startSearchIdx = -1;

    // TODO replace fixed weight by a dynamic one, e.g. based on average values
    this->lenWeight = 1;
    this->ampWeight = 200;
    this->peaksWeight = 1;
}

int WsSelector::findBestIdx(float inDesiredDur, float desiredRMS, int desiredPeaks, float lookBackLimit)
{
    int inDesiredLen = (int) (inDesiredDur * 44100.0)+0.5f; // convert dur to samples
    this->setSearchParams(inDesiredLen,desiredRMS,desiredPeaks,lookBackLimit);
    this->findBestIdx();
    return this->bestIdx;
}

/**
 * @brief Set the search parameters, restart search if necessary.
 */

void WsSelector::setSearchParams(int desiredLen, float desiredAmp,int desiredPeaks,int lookBackLimit){

    // find WS idx to start searching depending on lookBackLimit
    int inStartSearchIdx;
    if(lookBackLimit>=0 && lookBackLimit < this->wsData->getNumWsInStorage()) {
        inStartSearchIdx = this->wsData->getLastWsIdx() - lookBackLimit;
    } else {
        inStartSearchIdx = this->wsData->getFirstWsIdx();
    }

    if(this->searchIdx<inStartSearchIdx) this->searchIdx = inStartSearchIdx;

    // check if we have to restart Searching
    if(desiredLen != this->desiredLen
            || desiredAmp != this->desiredRMS
            || desiredPeaks != this->desiredPeaks
            || this->bestIdx < inStartSearchIdx // last result out of lookback range?
            || inStartSearchIdx < this->startSearchIdx
            || !this->wsData->isValidWsIdx(this->bestIdx) // last result out of xing buffer range?
            //|| !this->wsData->audioBuf->isInRange(this->wsData->getWaveSet(this->bestIdx).start) // out of audio buffer range?
            )
    {
        // restart Searching by resetting variables
        this->desiredLen = desiredLen;
        this->desiredRMS = desiredAmp;
        this->desiredPeaks = desiredPeaks;
        this->startSearchIdx = inStartSearchIdx;
        this->searchIdx = inStartSearchIdx;
        this->bestIdx = this->searchIdx;
        this->bestDiff = FLT_MAX;
    }

}

/**
 * @brief Calculate the diff of features.
 */

float WsSelector::calcDiff(Waveset* ws){
    float diff=0.0;

    if(this->desiredLen!=-1) {
        float diffLen = this->lenWeight * abs(this->desiredLen-ws->getLength());
        diff += diffLen*diffLen;
    }

    if(this->desiredRMS>=0) {
        float diffRMS = this->ampWeight * fabs(this->desiredRMS-ws->getMetaData().rms);
        diff += diffRMS*diffRMS;
    }

    if(this->desiredPeaks>=0) {
        float diffPeaks = this->peaksWeight * abs(this->desiredPeaks-ws->getMetaData().peaks);
        diff += diffPeaks*diffPeaks;
    }

    return diff;
}


/**
 * @brief Find the index of the waveset with the smallest diff.
 * @param unit
 */

void WsSelector::findBestIdx(){

    // search for best WS idx
    if(this->desiredLen<0 && this->desiredRMS<0 && this->desiredPeaks<0)
    {
       this->bestIdx = this->wsData->getLastWsIdx();
    }
    else
    {
        int idx;
        for(idx = this->searchIdx; idx<=this->wsData->getLastWsIdx(); idx++)
        {
            Waveset* ws = this->wsData->getWaveSet(idx);

            float diff = calcDiff(ws);

            delete ws;

            if (diff <= this->bestDiff)
            {
                this->bestIdx = idx;
                this->bestDiff = diff;
            }

        }
        this->searchIdx = idx;

    }
}
