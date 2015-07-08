#include "RTWaveSetAnalysis.h"

/**
 * @brief RTWaveSetAnalysis_Ctor Constructor for the RTWaveSetAnalysis UGen.
 * @param unit
 */

void RTWaveSetAnalysis_Ctor( RTWaveSetAnalysis *unit ) {
    printf("RTWaveSetAnalysis_Ctor()\n");

    // 1. set the calculation function.
    SETCALC(RTWaveSetAnalysis_next);

    //RTWaveSetBase_Ctor(unit);
    unit->inBuffer = SoundRingBuffer::createInBuffer(ZIN0(0),unit);
    unit->zeroBuffer = SoundRingBuffer::createInBuffer(ZIN0(1),unit);

    // 3. calculate one sample of output.
    RTWaveSetAnalysis_next(unit, 1);
}

/**
 * @brief RTWaveSetAnalysis_next Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetAnalysis_next( RTWaveSetAnalysis *unit, int inNumSamples ) {

    float *in = IN(2);
    float *out = OUT(0);

    // Input Processing
    for ( int i=0; i<inNumSamples; ++i) {
        //out[i] = 0.0;

        float prev = unit->inBuffer->getLast();

        // save to Buffer
        unit->inBuffer->put(in[i]);

        // look for a -/+ zero crossing
        if(prev <= 0.0 && in[i] > 0.0) {
            // add zero crossing position to zeroBuffer
            unit->zeroBuffer->put(unit->inBuffer->getLastPos());
            out[i] = 1.0;
        }
        else {
            out[i] = 0.0;
        }
    }

}

void RTWaveSetAnalysis_Dtor( RTWaveSetAnalysis *unit ) {

}
