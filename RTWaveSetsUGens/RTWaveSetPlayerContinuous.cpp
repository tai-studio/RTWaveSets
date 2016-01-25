#include "RTWaveSetPlayerContinuous.h"

void RTWaveSetPlayerContinuous_Ctor(RTWaveSetPlayerContinuous *unit){

    RTWaveSetPlayer_Ctor(unit);

    unit->wsIterator = WaveSetIterator();

    SETCALC(RTWaveSetPlayerContinuous_next);
    RTWaveSetPlayerContinuous_next(unit, 1);
}


/**
 * @brief Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetPlayerContinuous_next(RTWaveSetPlayerContinuous *unit, int inNumSamples){

    // ^this.multiNew('audio', audioBuf, wsBuf, trig, idx, rate, groupSize, repeat)

    // Inputs:
    float *idxInFloat = IN(2);
    float rate = IN0(3);
    float groupSize = IN0(4);
    float repeat = IN0(5);
    // Outputs:
    float *out = OUT(0);

    // WaveSet Playback
    for ( int i=0; i<inNumSamples; ++i) {

        // get Index Input
        int idxIn = (int) idxInFloat[i];

        // check index input
        if(unit->wsBuf->isInRange(idxIn)){
            // Start next Playback on End
            if(unit->wsIterator.endOfPlay()){
                RTWaveSetPlayer_playNextWS(&unit->wsIterator, unit,(int) repeat,(int) groupSize,idxIn ,rate);
            }
        }

        // Play WaveSets from Iterator
        if(unit->wsIterator.endOfPlay()) {
            out[i]=0.0;
        }
        else {
            out[i] = unit->audioBuf->get(unit->wsIterator.next());
        }
    }


}


void RTWaveSetPlayerContinuous_Dtor(RTWaveSetPlayerContinuous *unit){
    RTWaveSetPlayer_Dtor(unit);
}
