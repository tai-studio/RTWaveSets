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

    float param = IN0(3);

    int repeat = 1;
    if(param>1 && param <= unit->audioBuf->getLen()/maxWavesetLength) {
        // check if repeat Parameter is valid and doesn't exceed the buffer size
        repeat = (int) param;
    }
    unit->wsp.playWS(RTWaveSetPlayer_latesWSinRange(unit,minWavesetLength,maxWavesetLength),repeat,1);
}

void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Dtor(unit);
}
