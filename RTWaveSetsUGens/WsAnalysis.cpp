#include "WsAnalysis.h"

/**
 * @brief Constructur, just set the wsData variable.
 * @param wsData
 */

WsAnalysis::WsAnalysis(WaveSetData wsData) : wsData(wsData)
{
    reset();
}

/**
 * @brief Reset the running analysis.
 */

void WsAnalysis::reset()
{
    this->lastIn = NAN;
    this->lastXing = -1;
}

/**
 * @brief receive Audio Input.
 * @param audioIn
 * @param minWSLen
 */
void WsAnalysis::nextInputSample(float audioIn, int minWSLen)
{
    // save to Buffer
    wsData.audioBuf->put(audioIn);

    // look for a -/+ zero crossing
    if(this->lastIn <= 0.0 && audioIn > 0.0)
    {
        // add zero crossing position to zeroBuffer
        gotXing(minWSLen);
    }

    this->lastIn = audioIn;
}



int WsAnalysis::getFirstWsIdx()
{
    return wsData.wsBuf->getFirstPos();
}

int WsAnalysis::getLastWsIdx()
{
    return wsData.wsBuf->getLastPos();
}

void WsAnalysis::gotXing(int minWSLen)
{
    int currentXing = wsData.audioBuf->getLastPos();

    if(lastXing!=-1)
    {
        int start = lastXing;
        int end = currentXing;
        int wsLen = end - start;

        // check WaveSet length
        if(wsLen > minWSLen)
        {
            // save waveset
            float amp = calcRMS(start,end);
            WaveSet ws(start, end, amp);
            wsData.wsBuf->put(ws);
            lastXing = currentXing;
        }

    }
    else
    {
        lastXing = currentXing;
    }

}


/**
 * @brief Calculate the RMS of a waveset signal.
 * @param start
 * @param end
 * @return
 */

float WsAnalysis::calcRMS(int start,int end){
    float amp = 0.0;

    for(int idx=start;idx<end;idx++) // TODO inclusive or exclusive end? also relevant for length, playback
    {
        float val = wsData.audioBuf->get(idx);
        amp += val*val;
    }

    amp = sqrtf(amp / (end-start));
    return amp;
}
