#include "RTWaveSetPlayerRepeat.h"

void RTWaveSetPlayerRepeat_Ctor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Ctor(unit);
    unit->lastXingIdx = -1;
    unit->prevTrig = 1.0;
    SETCALC(RTWaveSetPlayerRepeat_next);
    RTWaveSetPlayerRepeat_next(unit, 1);

    unit->wsIterator = WaveSetIterator();
    // init WaveSetIterators
    for(int i=0;i<RTWaveSetPlayerRepeat_NumIterators;i++)
    {
        unit->wsIterators[i] = WaveSetIterator();
    }
}


/**
 * @brief Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetPlayerRepeat_next(RTWaveSetPlayerRepeat *unit, int inNumSamples){

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
        if(trig[i]>0.0 && unit->prevTrig<=0.0 && unit->xingsBuf->getLastPos()>=1)
        {

            // We have a Trigger, get WaveSet and set Iterator:

            // look for a free WaveSetIterator
            for(int playIdx=0;playIdx<RTWaveSetPlayerRepeat_NumIterators;playIdx++)
            {
                WaveSetIterator* wsi = &unit->wsIterators[playIdx];
                if(wsi->left()<1){
                    RTWaveSetPlayerRepeat_playNextWS(wsi, unit,(int) repeat,(int) numWS,idxIn + idxOffset,rate);
                    break;
                }

                if(playIdx==RTWaveSetPlayerRepeat_NumIterators-1)
                {
                    printf("RTWaveSetPlayerRepeat Warning: Number of parallel WaveSet playback exceeded!\n");
                }

            }

        }

        // Play WaveSets from Iterators
        float outSum = 0.0;
        for(int playIdx=0;playIdx<RTWaveSetPlayerRepeat_NumIterators;playIdx++)
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

void RTWaveSetPlayerRepeat_playNextWS(WaveSetIterator* wsi,RTWaveSetPlayerRepeat *unit,int repeat, int numWS, int xingIdx, float rate){

    int minWSinBuffer = unit->audioBuf->getLen()/maxWavesetLength;

    // check input Parameters
    if(!(repeat>1 && repeat <= minWSinBuffer)) repeat = 1;
    if(numWS < 0) numWS = 1;
    if(numWS > minWSinBuffer) numWS = minWSinBuffer;

    WaveSet ws = RTWaveSetPlayer_getWS(unit,xingIdx,numWS);

    printf_debug("RTWaveSetPlayerRepeat_playNextWS(rep=%i,numWS=%i,xingIdx=%i,rate=%f) len=%i xingIdx(%i,%i) bufferIdx(%i,%i) xingBufRange(%i,%i) audioBufRange(%i,%i)\n",
                 repeat,numWS,xingIdx,rate,
                 ws.end-ws.start,
                 xingIdx,xingIdx+numWS,ws.start,ws.end,
                 unit->xingsBuf->getLastPos()-unit->xingsBuf->getLen(),unit->xingsBuf->getLastPos(),
                 unit->audioBuf->getLastPos()-unit->audioBuf->getLen(),unit->audioBuf->getLastPos());

    wsi->playWS(ws,repeat,rate);
    printf_debug("wsi->left() = %i\n",wsi->left());
}

void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Dtor(unit);
}
