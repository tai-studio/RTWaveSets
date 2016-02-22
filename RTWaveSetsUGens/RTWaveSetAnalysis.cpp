#include "RTWaveSetAnalysis.h"


// define RTWaveSetAnalysis_DEBUG

/**
 * @brief RTWaveSetAnalysis_Ctor Constructor for the RTWaveSetAnalysis UGen.
 * @param unit
 */

void RTWaveSetAnalysis_Ctor( RTWaveSetAnalysis *unit ) {

    printf_debug("RTWaveSetAnalysis_Ctor()\n");

    RTWaveSetBase_Ctor(unit);
    unit->wsAnalysis = WsAnalysis(unit->wsData);

    // set the calculation function.
    SETCALC(RTWaveSetAnalysis_next);

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
    int minWsLen = int (inMinWaveSetLengthSec * unit->mWorld->mFullRate.mSampleRate + 0.5f); // convert in samples and round

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


/**
 * @brief RTWaveSetAnalysis_Dtor Destructor.
 * @param unit
 */

void RTWaveSetAnalysis_Dtor( RTWaveSetAnalysis *unit ) {

}

