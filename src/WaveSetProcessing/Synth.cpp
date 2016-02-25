#include "Synth.h"

Synth::Synth()
{

}

int Synth::foldIdx(int xingIdx){
    // fold idx if its out of range
     if(!wsData->wsBuf->isInRange(xingIdx)){

         // fold within available wavesets
         xingIdx = xingIdx % wsData->wsBuf->getLen();

         // shift in absolute buffer range
         while(xingIdx < wsData->wsBuf->getFirstPos()) {
             xingIdx += wsData->wsBuf->getSize();
         }

     }

     return xingIdx;
}

void Synth::playGroup(WsPlayer *player, float repeat, int groupSize, int xingIdx, float rate)
{
    xingIdx = foldIdx(xingIdx);
    if(!wsData->wsBuf->isInRange(xingIdx)) throw "RTWaveSetPlayer_playNextWS() Error: Waveset idx out of range!";
    WaveSetPlay ws = getGroup(xingIdx,groupSize);
    player->playWS(ws,repeat,rate);
}

// TODO move to WsData
WaveSetPlay Synth::getGroup(int wsIdx, int groupSize){

    if(groupSize < 1) groupSize = 1;

    WaveSetPlay ws;
    ws.start = -1;
    ws.end = -1;

    if(wsData->wsBuf->isInRange(wsIdx) && groupSize<wsData->wsBuf->getLen())
    {
        int startIdx = wsIdx-groupSize/2;
        int endIdx = startIdx + groupSize - 1;

        // shift back if we are at the end
        if(endIdx>wsData->wsBuf->getLastPos())
        {
            endIdx = wsData->wsBuf->getLastPos();
            startIdx = endIdx - groupSize + 1;
        }

        // shift forward if we are on the beginning
        if(startIdx<wsData->wsBuf->getFirstPos()){
            startIdx = wsData->wsBuf->getFirstPos();
            endIdx = startIdx + groupSize - 1;
        }

        // check validity of parameters
        if(groupSize<1) {
            printf("RTWaveSetPlayer Warning: numWS < 1\n");
            return ws;
        }

        int start = wsData->wsBuf->get(startIdx).start;
        int end = wsData->wsBuf->get(endIdx).end;

        if(isnan(end) || isnan(start) || end<1 || start<0)
        {
            printf("RTWaveSetPlayer Warning: no valid WaveSet found in xing Buffer!\n");
            return ws;
        }

        ws.end = end;
        ws.start = start;
    }

    return ws;
}


// TODO move to AudioPiece
float Synth::getSampleInterpolated(double idx)
{
    float sampleVal;

    // check if interpolation is needed
    bool doInterpolation = fabs(ceilf(idx)-idx)>0.01; // interpolate only > 1% offset

    if(doInterpolation)
    {
        int idxInt = (int) idx;
        float idxFrac = (double) idx - (double) idxInt;

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
        int idxRound = (int) (idx+0.5f);
        sampleVal= wsData->audioBuf->get(idxRound);
    }

    return sampleVal;
}

