#include "RTWaveSetPlayerTriggered.h"

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Ctor(unit);
    unit->lastXingIdx = -1;
    unit->prevTrig = 1.0;
    SETCALC(RTWaveSetPlayerTriggered_next);
    RTWaveSetPlayerTriggered_next(unit, 1);

    unit->wsIterator = WaveSetIterator();
    // init WaveSetIterators
    for(int i=0;i<RTWaveSetPlayerTriggered_NumIterators;i++)
    {
        unit->wsIterators[i] = WaveSetIterator();
    }
}


/**
 * @brief Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples){

    float *out = OUT(0);
    float repeat = IN0(2);
    float numWS = IN0(3);
    float *idxInFloat = IN(4);
    float *trig = IN(5);
    int idxOffset = IN0(6);
    float rate = IN0(7);


    // WaveSet Playback
    for ( int i=0; i<inNumSamples; ++i) {

        // get Index Input
        int idxIn = (int) idxInFloat[i];

        // check for Trigger and at least 2 crossings
        if(trig[i]>0.0 && unit->prevTrig<=0.0 && unit->wsBuf->getLastPos()>=1)
        {

            // We have a Trigger, get WaveSet and set Iterator:

            // look for a free WaveSetIterator
            for(int playIdx=0;playIdx<RTWaveSetPlayerTriggered_NumIterators;playIdx++)
            {
                WaveSetIterator* wsi = &unit->wsIterators[playIdx];
                if(wsi->left()<1){
                    RTWaveSetPlayerTriggered_playNextWS(wsi, unit,(int) repeat,(int) numWS,idxIn + idxOffset,rate);
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
                outSum+=unit->audioBuf->get(wsi->next());
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

void RTWaveSetPlayerTriggered_playNextWS(WaveSetIterator* wsi,RTWaveSetPlayerTriggered *unit,int repeat, int numWS, int xingIdx, float rate){

    int minWSinBuffer = unit->audioBuf->getLen()/maxWavesetLength;

    // check input Parameters
    if(!(repeat>1 && repeat <= minWSinBuffer)) repeat = 1;
    if(numWS < 0) numWS = 1;
    if(numWS > minWSinBuffer) numWS = minWSinBuffer;

    WaveSetPlay ws = RTWaveSetPlayer_getWS(unit,xingIdx,numWS);

    printf_debug("RTWaveSetPlayerTriggered_playNextWS(rep=%i,numWS=%i,xingIdx=%i,rate=%f) len=%i wsIdx(%i,%i) audioIdx(%i,%i) wsBufRange(%i,%i) audioBufRange(%i,%i)\n",
                 repeat,numWS,xingIdx,rate,
                 ws.end-ws.start,
                 xingIdx,xingIdx+numWS-1,ws.start,ws.end,
                 unit->wsBuf->getFirstPos(),unit->wsBuf->getLastPos(),
                 unit->audioBuf->getFirstPos(),unit->audioBuf->getLastPos());

    wsi->playWS(ws,repeat,rate);
    printf_debug("wsi->left() = %i\n",wsi->left());
}

void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Dtor(unit);
}
