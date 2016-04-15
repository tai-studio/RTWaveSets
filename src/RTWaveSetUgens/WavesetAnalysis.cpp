#include "WavesetAnalysis.h"

/**
 * @brief WavesetAnalysis_Ctor Constructor for the WavesetAnalysis UGen.
 * @param unit
 */

void WavesetAnalysis_Ctor( WavesetAnalysis *unit ) {

    WavesetBase_Ctor(unit);
    new (&unit->wsAnalysis) WsAnalysis(unit->wsData);

    // set the calculation function.
    SETCALC(WavesetAnalysis_next);

    // calculate one sample of output.
    WavesetAnalysis_next(unit, 1);
}

/**
 * @brief WavesetAnalysis_Dtor Destructor.
 * @param unit
 */

void WavesetAnalysis_Dtor( WavesetAnalysis *unit ) {
    unit->wsAnalysis.~WsAnalysis();
    WavesetBase_Dtor(unit);
}


/**
 * @brief WavesetAnalysis_next Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void WavesetAnalysis_next( WavesetAnalysis *unit, int inNumSamples ) {

    float *in = IN(2);
    float *out1 = OUT(0);
    float *out2 = OUT(1);
    float analysisOn = IN0(3);
    float inMinWavesetLengthSec = IN0(4);
    int minWsLen = int (inMinWavesetLengthSec * unit->mWorld->mFullRate.mSampleRate + 0.5f); // convert in samples and round

    // Input Processing
    for ( int i=0; i<inNumSamples; ++i)
    {

        if(analysisOn > 0.0) // analysis is running...
        {
            unit->wsAnalysis.nextInputSample(in[i],minWsLen);
        }
        else
        {
            unit->wsAnalysis.reset();
        }

        out1[i] = (float) unit->wsAnalysis.getFirstWsIdx();
        out2[i] = (float) unit->wsAnalysis.getLastWsIdx();
    }

}



