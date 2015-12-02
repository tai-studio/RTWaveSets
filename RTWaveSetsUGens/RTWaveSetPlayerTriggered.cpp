#include "RTWaveSetPlayerTriggered.h"

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Ctor(unit);
    unit->lastXingIdx = -1;
    unit->prevTrig = 1.0;

    // init WaveSetIterators
    for(int i=0;i<RTWaveSetPlayerTriggered_NumIterators;i++)
    {
        unit->wsIterators[i] = WaveSetIterator();
        if(unit->wsIterators[i].left()!=0) printf("RTWaveSetPlayerTriggered_Ctor() Error! WaveSetIterator initialized unproperly.");
    }

    SETCALC(RTWaveSetPlayerTriggered_next);
    RTWaveSetPlayerTriggered_next(unit, 1);
}


/**
 * @brief Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples){

    // ^this.multiNew('audio', audioBuf, wsBuf, trig, idx, rate, groupSize, repeat)

    // Inputs:
    float *trig = IN(2);
    float *idxInFloat = IN(3);
    float rate = IN0(4);
    float groupSize = IN0(5);
    float repeat = IN0(6);
    // Outputs:
    float *out = OUT(0);

    // WaveSet Playback
    for ( int i=0; i<inNumSamples; ++i) {

        // get Index Input
        int idxIn = (int) idxInFloat[i];

        // check for Trigger and at least one waveset
        if(trig[i]>0.0 && unit->prevTrig<=0.0 && unit->wsBuf->getLastPos()>=1)
        {

            // We have a Trigger, get WaveSet and set Iterator:



            // look for a free WaveSetIterator
            for(int playIdx=0;playIdx<RTWaveSetPlayerTriggered_NumIterators;playIdx++)
            {
                WaveSetIterator* wsi = &unit->wsIterators[playIdx];
                if(wsi->left()<1){
                    RTWaveSetPlayerTriggered_playNextWS(wsi, unit,(int) repeat,(int) groupSize,idxIn ,rate);
                    break;
                }

                if(playIdx==RTWaveSetPlayerTriggered_NumIterators-1)
                {
                    printf("RTWaveSetPlayerTriggered Warning: Number of parallel WaveSet playback exceeded!\n");
                }

            }

        }

        // Play WaveSets from Iterators
        float outSum = 0.0;
        for(int playIdx=0;playIdx<RTWaveSetPlayerTriggered_NumIterators;playIdx++)
        {
            WaveSetIterator* wsi = &unit->wsIterators[playIdx];
            // play parallel WaveSets from Iterators
            if(wsi->left()>0)
            {
                    int idx = wsi->next();
                    if(unit->audioBuf->isInRange(idx)) {
                        outSum += unit->audioBuf->get(idx);
                    } else {
                        printf("WaveSet playback failed! (out of audio buffer Range)\n");
                        *wsi = WaveSetIterator(); // stop playback by resetting
                    }
            }

        }
        out[i] = outSum;

        unit->prevTrig=trig[i];
        unit->lastXingIdx = idxIn;
    }


}

/**
 * @brief Load the next WaveSet to play.
 * @param unit
 */

void RTWaveSetPlayerTriggered_playNextWS(WaveSetIterator* wsi,RTWaveSetPlayerTriggered *unit,int repeat, int groupSize, int xingIdx, float rate){

    int minWSinBuffer = unit->audioBuf->getSize()/maxWavesetLength;

    // check input Parameters
    //if(!(repeat>1 && repeat <= minWSinBuffer)) repeat = 1; // TODO is this necessary?
    if(groupSize < 0) groupSize = 1;
    if(groupSize > minWSinBuffer) groupSize = minWSinBuffer;
    // TODO: check if xingIdx is in Buffer Range

    WaveSetPlay ws = RTWaveSetPlayer_getWS(unit,xingIdx,groupSize);

    printf_debug("RTWaveSetPlayerTriggered_playNextWS(rep=%i,numWS=%i,xingIdx=%i,rate=%f) len=%i wsIdx(%i,%i) audioIdx(%i,%i) wsBufRange(%i,%i) audioBufRange(%i,%i)\n",
                 repeat,groupSize,xingIdx,rate,
                 ws.end-ws.start,
                 xingIdx,xingIdx+groupSize-1,ws.start,ws.end,
                 unit->wsBuf->getFirstPos(),unit->wsBuf->getLastPos(),
                 unit->audioBuf->getFirstPos(),unit->audioBuf->getLastPos());

    wsi->playWS(ws,repeat,rate);
    printf_debug("wsi->left() = %i\n",wsi->left());
}

void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Dtor(unit);
}
