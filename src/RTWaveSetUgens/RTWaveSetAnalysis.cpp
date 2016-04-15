#include "RTWavesetAnalysis.h"

/**
 * @brief RTWavesetAnalysis_Ctor Constructor for the RTWavesetAnalysis UGen.
 * @param unit
 */

void RTWavesetAnalysis_Ctor( RTWavesetAnalysis *unit ) {

    RTWavesetBase_Ctor(unit);
    new (&unit->wsAnalysis) WsAnalysis(unit->wsData);

    // set the calculation function.
    SETCALC(RTWavesetAnalysis_next);

    // calculate one sample of output.
    RTWavesetAnalysis_next(unit, 1);
}

/**
 * @brief RTWavesetAnalysis_Dtor Destructor.
 * @param unit
 */

void RTWavesetAnalysis_Dtor( RTWavesetAnalysis *unit ) {
    unit->wsAnalysis.~WsAnalysis();
    RTWavesetBase_Dtor(unit);
}


/**
 * @brief RTWavesetAnalysis_next Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWavesetAnalysis_next( RTWavesetAnalysis *unit, int inNumSamples ) {

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



