#include "RTWaveSetPlayerTriggered.h"

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit){

    // init UGen
    RTWaveSetBase_Ctor(unit);
    new (&unit->wsSynth) SynthTriggered(&unit->wsData);
    unit->prevTrig = 1.0;


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

        // check for Trigger and valid idx input
        if(trig[i]>0.0 && unit->prevTrig<=0.0 && idxIn >= 0)
        {
            // we have a trigger, star new playback
            unit->wsSynth.startNewPlayback(idxIn,groupSize,rate,repeat);

        }


        // get Output
        float outSum = unit->wsSynth.getNextOutput();

        out[i] = outSum;

        unit->prevTrig=trig[i];

    }


}


void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit){

}
