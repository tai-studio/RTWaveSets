#include "RTWaveSetPlayerRepeat.h"

void RTWaveSetPlayerRepeat_Ctor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Ctor(unit);
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

    // WaveSet Playback
    for ( int i=0; i<inNumSamples; ++i) {
        // Samples left in WaveSetPlayer?
        if(unit->wsp.left()<1 && unit->xingsBuf->getLastPos()>=1) {
            RTWaveSetPlayerRepeat_playNextWS(unit);
        }

        // play WaveSet
        if(unit->wsp.left()>0) {
            out[i] = unit->audioBuf->get(unit->wsp.next());
        }
        else{
            out[i] = 0.0;
        }
    }

}

/**
 * @brief Load the next WaveSet to play.
 * @param unit
 */

void RTWaveSetPlayerRepeat_playNextWS(RTWaveSetPlayerRepeat *unit){

    int repeat = 1;
    int backIdx = 0;
    int numWS = 1;

    float in_repeat = IN0(3);

    // check if repeat Parameter is valid and doesn't exceed the buffer size
    if(in_repeat>1 && in_repeat <= unit->audioBuf->getLen()/maxWavesetLength) {
        repeat = (int) in_repeat;
    }

    WaveSet ws = RTWaveSetPlayer_getWS(unit,backIdx,numWS);
    unit->wsp.playWS(ws,repeat,1);
}

void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Dtor(unit);
}
