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
        if(idxIn>=0){
            // Start next Playback on End
            if(unit->wsIterator.endOfPlay()){
                RTWaveSetPlayer_playNextWS(&unit->wsIterator, unit,(int) repeat,(int) groupSize,idxIn ,rate);
            }
        }

        float outSample = 0.0;

        // Play WaveSets from Iterator
        try
        {
            if(!unit->wsIterator.endOfPlay()) {
                float nextIdx = unit->wsIterator.next();
                if(unit->audioBuf->isInRange((int)nextIdx)){
                    outSample = RTWaveSetPlayer_getSample(unit,nextIdx);
                }
                else{
                    printf("WaveSet playback failed! (out of audio buffer Range)\n");
                    unit->wsIterator = WaveSetIterator(); // stop playback by resetting
                }
            }
        }
        catch(...)
        {
            printf("WaveSet playback failed! (unknown exception)\n");
            unit->wsIterator = WaveSetIterator(); // stop playback by resetting
        }

        out[i] = outSample;
    }


}


void RTWaveSetPlayerContinuous_Dtor(RTWaveSetPlayerContinuous *unit){
    RTWaveSetPlayer_Dtor(unit);
}
