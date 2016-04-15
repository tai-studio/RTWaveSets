#include "WavesetSynthContinuous.h"

void WavesetSynthContinuous_Ctor(WavesetSynthContinuous *unit){

    WavesetBase_Ctor(unit);
    new (&unit->wsSynth) SynthContinuous(unit->wsData);

    SETCALC(WavesetSynthContinuous_next);
    WavesetSynthContinuous_next(unit, 1);
}


/**
 * @brief Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void WavesetSynthContinuous_next(WavesetSynthContinuous *unit, int inNumSamples){

    // ^this.multiNew('audio', audioBuf, wsBuf, trig, idx, rate, groupSize, repeat)

    // Inputs:
    float *idxInFloat = IN(2);
    float rate = IN0(3);
    float groupSize = IN0(4);
    float repeat = IN0(5);
    // Outputs:
    float *out = OUT(0);

    // Waveset Playback
    for ( int i=0; i<inNumSamples; ++i) {

        // get Index Input
        int idxIn = (int) idxInFloat[i];

        unit->wsSynth.setNext(idxIn, groupSize, rate, repeat);
        float outSample = unit->wsSynth.getNextOutput();

        out[i] = outSample;
    }


}


void WavesetSynthContinuous_Dtor(WavesetSynthContinuous *unit){

}
