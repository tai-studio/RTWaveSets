#include "RTWaveSetAnalysis.h"
// define RTWaveSetAnalysis_DEBUG

/**
 * @brief RTWaveSetAnalysis_Ctor Constructor for the RTWaveSetAnalysis UGen.
 * @param unit
 */

void RTWaveSetAnalysis_Ctor( RTWaveSetAnalysis *unit ) {

    printf_debug("RTWaveSetAnalysis_Ctor()\n");

    RTWaveSetBase_Ctor(unit);

    // set the calculation function.
    SETCALC(RTWaveSetAnalysis_next);

    unit->lastXing = -1;
    unit->lastAnalysisOn = -1;
    unit->minWavesetLength = -1;

    // calculate one sample of output.
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
    float *out1 = OUT(0);
    float *out2 = OUT(1);
    float analysisOn = IN0(3);
    float inMinWaveSetLengthSec = IN0(4);
    unit->minWavesetLength = int (inMinWaveSetLengthSec * unit->mWorld->mFullRate.mSampleRate + 0.5f); // convert in samples and round

    // Input Processing
    for ( int i=0; i<inNumSamples; ++i)
    {

        if(analysisOn > 0.0) // analysis is running...
        {
            // save to Buffer
            unit->wsData.audioBuf->put(in[i]);

            // do analysis only if we have at least two continuous samples
            if(unit->lastAnalysisOn > 0.0)
            {
                float prev = unit->wsData.audioBuf->getLast(1);

                // look for a -/+ zero crossing
                if(prev <= 0.0 && in[i] > 0.0)
                {
                    // add zero crossing position to zeroBuffer
                    RTWaveSetAnalysis_gotXing(unit);
                }
            }
        }

        unit->lastAnalysisOn = analysisOn;
        out1[i] = (float) unit->wsData.wsBuf->getFirstPos();
        out2[i] = (float) unit->wsData.wsBuf->getLastPos();

    }

    unit->wsData.cleanUp();

}

/**
 * @brief Check length and add zerocrossing to buffer.
 * @param unit
 */

void RTWaveSetAnalysis_gotXing(RTWaveSetAnalysis *unit)
{
    int currentXing = unit->wsData.audioBuf->getLastPos();

    if(unit->lastXing!=-1) {
        int start = unit->lastXing;
        int end = currentXing;
        int wsLen = end - start;

        // check WaveSet length
        if(wsLen > unit->minWavesetLength) {
            float amp = RTWaveSetAnalysis_calcRMS(unit,start,end);

            WaveSet ws(unit->lastXing, currentXing, amp);
            unit->wsData.wsBuf->put(ws);
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

float RTWaveSetAnalysis_calcRMS(RTWaveSetAnalysis *unit, int start, int end){

    float amp = 0.0;

    for(int idx=start;idx<end;idx++) // TODO inclusive or exclusive end? also relevant for length
    {
        float val = unit->wsData.audioBuf->get(idx);
        amp += val*val;
    }

    amp = sqrtf(amp / (end-start));
    return amp;
}
