#include "RTWaveSetAnalysis.h"
// define RTWaveSetAnalysis_DEBUG

/**
 * @brief RTWaveSetAnalysis_Ctor Constructor for the RTWaveSetAnalysis UGen.
 * @param unit
 */

void RTWaveSetAnalysis_Ctor( RTWaveSetAnalysis *unit ) {

    printf_debug("RTWaveSetAnalysis_Ctor()\n");

    // 1. set the calculation function.
    SETCALC(RTWaveSetAnalysis_next);

    unit->audioBuf = FloatRingBuffer::createInBuffer(ZIN0(0),unit);
    unit->wsBuf = WaveSetRingBuffer::createInBuffer(ZIN0(1),unit);
    unit->lastXing = -1;

    // 3. calculate one sample of output.
    RTWaveSetAnalysis_next(unit, 1);
}

/**
 * @brief RTWaveSetAnalysis_next Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 * TODO: Handle broken WaveSets when analysis was switched Off and ON.
 */

void RTWaveSetAnalysis_next( RTWaveSetAnalysis *unit, int inNumSamples ) {

    float *in = IN(2);
    float *out = OUT(0);
    float analysisOn = IN0(3);

    // Input Processing
    for ( int i=0; i<inNumSamples; ++i)
    {
        float prev = unit->audioBuf->getLast();

        if(analysisOn > 0.0)
        {
            // save to Buffer
            unit->audioBuf->put(in[i]);

            // look for a -/+ zero crossing
            if(prev <= 0.0 && in[i] > 0.0) {

                // add zero crossing position to zeroBuffer
                RTWaveSetAnalysis_gotXing(unit);
            }
        }

        out[i] = (float) unit->wsBuf->getLastPos();

}

}

/**
 * @brief Check length and add zerocrossing to buffer.
 * @param unit
 */

void RTWaveSetAnalysis_gotXing(RTWaveSetAnalysis *unit)
{
    int currentXing = unit->audioBuf->getLastPos();

    if(unit->lastXing!=-1) {
        int start = unit->lastXing;
        int end = currentXing;
        int wsLen = end - start;

        // check WaveSet length
        if(wsLen > RTWaveSetAnalysis_minWavesetLength) {
            float amp = RTWaveSetAnalysis_calcAmp(unit,start,end);

            WaveSet ws(unit->lastXing, currentXing, amp);
            unit->wsBuf->put(ws);
            unit->lastXing = currentXing;
            // #ifdef RTWaveSetAnalysis_DEBUG
            // printf("RTWaveSetAnalysis_gotXing() xingIdx:%i wsLen: %i\n",unit->xingsBuf->getLastPos(),wsLen);
            // #endif
        }
      } else {
        unit->lastXing = currentXing;
    }

}

/**
 * @brief RTWaveSetAnalysis_Dtor Destructor.
 * @param unit
 */

void RTWaveSetAnalysis_Dtor( RTWaveSetAnalysis *unit ) {

}

/**
 * @brief Calculate the RMS of the WaveSets signal.
 * @param unit
 * @return
 */

float RTWaveSetAnalysis_calcAmp(RTWaveSetAnalysis *unit, int start, int end){

    float amp = 0.0;

    for(int idx=start;idx<end;idx++) // TODO inclusive or exclusive end? also relevant for length
    {
        float val = unit->audioBuf->get(idx);
        amp += val*val;
    }

    amp = sqrtf(amp / (end-start));
    return amp;
}
