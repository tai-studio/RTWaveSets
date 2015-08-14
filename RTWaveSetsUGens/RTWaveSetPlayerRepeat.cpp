#include "RTWaveSetPlayerRepeat.h"
// #define RTWaveSetPlayerRepeat_DEBUG

void RTWaveSetPlayerRepeat_Ctor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Ctor(unit);
    unit->lastXingIdx = -1;
    SETCALC(RTWaveSetPlayerRepeat_next);
    RTWaveSetPlayerRepeat_next(unit, 1);
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
    int hold = IN0(5);
    int idxOffset = IN0(6);


    // WaveSet Playback
    for ( int i=0; i<inNumSamples; ++i) {

        //int hold = (int) holdF[i];
        int idxIn;

        if(!hold){
            idxIn = (int) idxInFloat[i];
        }else{
            idxIn = unit->lastXingIdx;
        }

        // Samples left in WaveSetPlayer?
        if(unit->wsp.left()<1 && unit->xingsBuf->getLastPos()>=1) {
            #ifdef RTWaveSetPlayerRepeat_DEBUG
            printf("RTWaveSetPlayerRepeat_next: idxIn:%i idxOffset:%i hold:%i\n",idxIn,idxOffset,hold);
            #endif
            RTWaveSetPlayerRepeat_playNextWS(unit,(int) repeat,(int) numWS,idxIn + idxOffset);
        }

        // play WaveSet
        if(unit->wsp.left()>0) {
            out[i] = unit->audioBuf->get(unit->wsp.next());
        }
        else{
            out[i] = 0.0;
        }

        unit->lastXingIdx = idxIn;
    }

}

/**
 * @brief Load the next WaveSet to play.
 * @param unit
 */

void RTWaveSetPlayerRepeat_playNextWS(RTWaveSetPlayerRepeat *unit,int repeat, int numWS, int xingIdx){


    #ifdef RTWaveSetPlayerRepeat_DEBUG
    printf("RTWaveSetPlayerRepeat_playNextWS() xingIdx:%i\n",xingIdx);
    #endif

    int minWSinBuffer = unit->audioBuf->getLen()/maxWavesetLength;

    // check input Parameters
    if(!(repeat>1 && repeat <= minWSinBuffer)) repeat = 1;
    if(numWS < 0) numWS = 1;
    if(numWS > minWSinBuffer) numWS = minWSinBuffer;

    WaveSet ws = RTWaveSetPlayer_getWS(unit,xingIdx,numWS);
    unit->wsp.playWS(ws,repeat,1);
}

void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Dtor(unit);
}
