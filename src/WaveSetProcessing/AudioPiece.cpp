#include "AudioPiece.h"

AudioPiece::AudioPiece()
{
    this->wsData = NULL;
    this->start = -1;
    this->end = -1;
}

AudioPiece::AudioPiece(WsStorageDualBuf* wsData,int start,int end)
{
    this->wsData = wsData;
    this->start = start;
    this->end = end;
}

/**
 * @brief AudioPiece::getSampleInterpolated
 * @param pos postion within aduio pice 0...len-1
 * @return
 */

float AudioPiece::getSampleInterpolated(double pos)
{
    float sampleVal;

    // start idx as base
    double floatIdx = pos + this->start;

    // split int and fractional Part
    int idxInt = (int) floatIdx;
    float idxFrac = (double) floatIdx - (double) idxInt;

    // check idx range
    if(!wsData->audioBuf->isInRange(idxInt)) throw "WaveSet playback failed! (out of audio buffer Range)\n";

    // check if interpolation is needed
    bool doInterpolation = fabs(ceilf(floatIdx)-floatIdx)>0.01; // interpolate only > 1% offset

    if(doInterpolation)
    {
        // check the available data range for interpolation
        if(wsData->audioBuf->isInRange(idxInt-1) && wsData->audioBuf->isInRange(idxInt+2))
        {
            // cubic interpolation:
            float y0 = wsData->audioBuf->get(idxInt-1);
            float y1 = wsData->audioBuf->get(idxInt);
            float y2 = wsData->audioBuf->get(idxInt+1);
            float y3 = wsData->audioBuf->get(idxInt+2);

            sampleVal = cubicinterp(idxFrac,y0,y1,y2,y3);
        }
        else if(wsData->audioBuf->isInRange(idxInt+1))
        {
            // linear iterpolation:
            float y1 = wsData->audioBuf->get(idxInt);
            float y2 = wsData->audioBuf->get(idxInt+1);
            sampleVal = lininterp(idxFrac,y1,y2);
        }
        else{
            // no interpolation:
            doInterpolation = false;
        }

    }

    if(!doInterpolation)
    {
        // no interpolation:
        int idxRound = (int) (floatIdx+0.5f);
        sampleVal= wsData->audioBuf->get(idxRound);
    }

    return sampleVal;
}

