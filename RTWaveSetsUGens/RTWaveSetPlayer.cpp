#include "RTWaveSetPlayer.h"
// define RTWaveSetPlayer_DEBUG


/**
 * @brief RTWaveSetPlayer_Ctor Constructor for the RTWaveSetPlayer UGen.
 * @param unit
 */

void RTWaveSetPlayer_Ctor( RTWaveSetPlayer *unit ) {
    RTWaveSetBase_Ctor(unit);

}



/**
 * @brief Get the latest Waveset that is in the given size range.
 * @param unit
 * @param minWavesetLength
 * @param maxWavesetLength
 * @return The WaveSet.
 */

WaveSetPlay RTWaveSetPlayer_latesWSinRange(RTWaveSetPlayer *unit, int minWavesetLength, int maxWavesetLength)
{
    WaveSetPlay ws;
    ws.start = -1;
    ws.end = -1;


    if(unit->wsBuf->getLastPos()>=1&& unit->audioBuf->getLastPos()>=maxWavesetLength)
    // wait for at least one zerocrossing and enouph input samples for a waveset mit max length
    {
        // zerocrossings "backward-index" of the waveset
        int endBack = 0;
        int startBack = endBack+1;

        // search for for a WaveSet with the right length, beginning at the end.
        int wsLen;
        do {
            ws.end=unit->wsBuf->getLast(endBack).start;
            ws.start=unit->wsBuf->getLast(startBack).start;
            wsLen = ws.end - ws.start;

            // if the Waveset it too long take the next one
            if(wsLen>maxWavesetLength)
            {
                endBack++;
                startBack = endBack+1;
                #ifdef RTWaveSetPlayer_DEBUG
                printf("RTWaveSetAnalysis_latesWSinRange() Warning: skipping too long WaveSet!");
                #endif
            }

            // if the WS is too short extend to the next zerocrossing.
            if(wsLen<minWavesetLength)
            {
                startBack++;
            }

            if(startBack > unit->wsBuf->getLastPos()) break; // give up when reached beginning

        } while(wsLen < minWavesetLength || wsLen > maxWavesetLength);
    }

    #ifdef RTWaveSetPlayer_DEBUG
    printf("RTWaveSetPlayer_getWS() len:%i\n",ws.end-ws.start);
    #endif
    return ws;
}

/**
 * @brief Get a WaveSet.
 * @param unit
 * @param wsIdx Index of the WaveSet.
 * @param groupSize How many sourrounding WaveSets should be appended.
 * @return
 */

WaveSetPlay RTWaveSetPlayer_getWS(RTWaveSetPlayer *unit, int wsIdx, int groupSize){
    WaveSetPlay ws;
    ws.start = -1;
    ws.end = -1;

    if(unit->wsBuf->isInRange(wsIdx) && groupSize<unit->wsBuf->getLen())
    {
        int startIdx = wsIdx-groupSize/2;
        int endIdx = startIdx + groupSize - 1;

        // shift back if we are at the end
        if(endIdx>unit->wsBuf->getLastPos())
        {
            endIdx = unit->wsBuf->getLastPos();
            startIdx = endIdx - groupSize + 1;
        }

        // shift forward if we are on the beginning
        if(startIdx<unit->wsBuf->getFirstPos()){
            startIdx = unit->wsBuf->getFirstPos();
            endIdx = startIdx + groupSize - 1;
        }

        // check validity of parameters
        if(groupSize<1) {
            printf("RTWaveSetPlayer Warning: numWS < 1\n");
            return ws;
        }

        int start = unit->wsBuf->get(startIdx).start;
        int end = unit->wsBuf->get(endIdx).end;

        if(isnan(end) || isnan(start) || end<1 || start<0)
        {
            printf("RTWaveSetPlayer Warning: no valid WaveSet found in xing Buffer!\n");
            return ws;
        }

        // cast to int
        ws.end = end;
        ws.start = start;
    }

    return ws;
}

/**
 * @brief Load the next WaveSet to play.
 * @param unit
 */

void RTWaveSetPlayer_playNextWS(WaveSetIterator* wsi,RTWaveSetPlayer *unit,int repeat, int groupSize, int xingIdx, float rate){

    // check input Parameters
    if(groupSize < 0) groupSize = 1;

    // fold idx if its out of range
     if(!unit->wsBuf->isInRange(xingIdx)){
         xingIdx = xingIdx % unit->wsBuf->getLen() + unit->wsBuf->getFirstPos();
     }

    if(unit->wsBuf->isInRange(xingIdx)){
        WaveSetPlay ws = RTWaveSetPlayer_getWS(unit,xingIdx,groupSize);

        printf_debug("RTWaveSetPlayerContinuous_playNextWS(rep=%i,numWS=%i,xingIdx=%i,rate=%f) len=%i wsIdx(%i,%i) audioIdx(%i,%i) wsBufRange(%i,%i) audioBufRange(%i,%i)\n",
                     repeat,groupSize,xingIdx,rate,
                     ws.end-ws.start,
                     xingIdx,xingIdx+groupSize-1,ws.start,ws.end,
                     unit->wsBuf->getFirstPos(),unit->wsBuf->getLastPos(),
                     unit->audioBuf->getFirstPos(),unit->audioBuf->getLastPos());

        wsi->playWS(ws,repeat,rate);
    }
    else{
        printf("RTWaveSetPlayer_playNextWS() Error: Waveset idx out of range!");
    }

}

void RTWaveSetPlayer_Dtor( RTWaveSetPlayer *unit ) {

}

/**
 * @brief Calculate the current sample for playback at given position.
 * If idx has an fractional and there is enouph data availabel cubic or linear interpolation is used if possible.
 * @param unit
 * @param idx
 * @return value of the sample
 * TODO: use really played samples at repeats and waveset gaps not the continuous recording for interpolation.
 */

float RTWaveSetPlayer_getSample(RTWaveSetPlayer *unit, float idx)
{
    float sampleVal;

    // check if interpolation is needed
    bool doInterpolation = fabs(ceilf(idx)-idx)>0.01; // interpolate only > 1% offset

    if(doInterpolation)
    {
        int idxInt = (int) idx;
        float idxFrac = idx - (float) idxInt;

        // check the available data range for interpolation
        if(unit->audioBuf->isInRange(idxInt-1) && unit->audioBuf->isInRange(idxInt+2))
        {
            // cubic interpolation:
            float y0 = unit->audioBuf->get(idxInt-1);
            float y1 = unit->audioBuf->get(idxInt);
            float y2 = unit->audioBuf->get(idxInt+1);
            float y3 = unit->audioBuf->get(idxInt+2);

            sampleVal = cubicinterp(idxFrac,y0,y1,y2,y3);
        }
        else if(unit->audioBuf->isInRange(idxInt+1))
        {
            // linear iterpolation:
            float y1 = unit->audioBuf->get(idxInt);
            float y2 = unit->audioBuf->get(idxInt+1);
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
        int idxRound = (int) (idx+0.5f);
        sampleVal= unit->audioBuf->get(idxRound);
    }

    return sampleVal;

}
