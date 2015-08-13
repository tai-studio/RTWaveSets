#include "RTWaveSetAnalysis.h"

/**
 * @brief RTWaveSetAnalysis_Ctor Constructor for the RTWaveSetAnalysis UGen.
 * @param unit
 */

void RTWaveSetAnalysis_Ctor( RTWaveSetAnalysis *unit ) {
    printf("RTWaveSetAnalysis_Ctor()\n");

    // 1. set the calculation function.
    SETCALC(RTWaveSetAnalysis_next);

    unit->checkWSlen = true;
    unit->audioBuf = SoundRingBuffer::createInBuffer(ZIN0(0),unit);
    unit->xingsBuf = SoundRingBuffer::createInBuffer(ZIN0(1),unit);

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

        float prev = unit->audioBuf->getLast();

        // save to Buffer
        unit->audioBuf->put(in[i]);

        // look for a -/+ zero crossing
        if(prev <= 0.0 && in[i] > 0.0) {

            // add zero crossing position to zeroBuffer
            RTWaveSetAnalysis_gotXing(unit);
        }

        out[i] = (float) unit->xingsBuf->getLastPos();

    }

}

/**
 * @brief Check length and add zerocrossing to buffer.
 * @param unit
 */

void RTWaveSetAnalysis_gotXing(RTWaveSetAnalysis *unit)
{
    if(unit->checkWSlen && unit->xingsBuf->getLastPos()>=0) {
        // check WaveSet length

        int lastXing = unit->xingsBuf->getLast();
        int currentXing = unit->audioBuf->getLastPos();
        int wsLen = currentXing - lastXing;

        if(wsLen > RTWaveSetAnalysis_minWavesetLength) {
            unit->xingsBuf->put(currentXing);
            //printf("RTWaveSetAnalysis_gotXing() xingIdx:%i wsLen: %i\n",unit->xingsBuf->getLastPos(),wsLen);
        }

    } else {
        // add xing without checking Length
        unit->xingsBuf->put(unit->audioBuf->getLastPos());

    }

}

/**
 * @brief RTWaveSetAnalysis_Dtor Destructor.
 * @param unit
 */

void RTWaveSetAnalysis_Dtor( RTWaveSetAnalysis *unit ) {

}
