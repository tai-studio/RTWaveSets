#include "AudioPieceDualBuf.h"
#include "WsStorageDualBuf.h"


AudioPieceDualBuf::AudioPieceDualBuf(WsStorageDualBuf* wsData,int start,int end)
{
    this->wsData = wsData;
    this->start = start;
    this->end = end;
}

float AudioPieceDualBuf::getSample(int pos)
{
    int idx = pos + this->start;
    if(!wsData->audioBuf->isInRange(idx)) throw "AudioPieceDualBuf::getSample failed! (out of audio buffer Range)\n";
    return wsData->audioBuf->get(idx);
}


/**
 * @brief Get the audio sample value at given position. If the floating point position is fractional the value will be interpolated.
 * @param pos Position within the AudioPieceDualBuf in the range from 0...Length-1.
 * @return
 */

float AudioPieceDualBuf::getSampleInterpolated(double pos)
{
    float sampleVal;

    // start idx as base
    double floatIdx = pos + this->start;

    // split int and fractional Part
    int idxInt = (int) floatIdx;
    float idxFrac = (double) floatIdx - (double) idxInt;
    int idxRound = (int) (floatIdx+0.5f);

    // check idx range
    if(!wsData->audioBuf->isInRange(idxRound)) throw "Waveset playback failed! (out of audio buffer Range)\n";

    // check if interpolation is needed
    bool doInterpolation = fabs(ceilf(floatIdx)-floatIdx) > interpThreshold; // interpolate only > 1% offset

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
        sampleVal= wsData->audioBuf->get(idxRound);
    }

    return sampleVal;
}

