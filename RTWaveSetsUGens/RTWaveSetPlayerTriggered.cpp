#include "RTWaveSetPlayerTriggered.h"

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Ctor(unit);
    SETCALC(RTWaveSetPlayerTriggered_next);

    unit->prevTrig = 1.0;
    unit->trigIdx = -1;
    unit->oldTrigIdx = -1;

    RTWaveSetPlayerTriggered_next(unit,1);

    // initialize the unit generator state variables.
    unit->wsp = WaveSetIterator();
}

void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples){
    float *out = OUT(0);
    float *trig = IN(3);

    // WaveSet Playback
    for ( int i=0; i<inNumSamples; ++i) {

        if(trig[i]>0.0 && unit->prevTrig<=0.0)
        {
            // Trigger Now!
            unit->trigIdx = unit->xingsBuf->getLastPos();
        }
        unit->prevTrig=trig[i];


        // Samples left in WaveSetPlayer?
        if(unit->wsp.left()<1 && unit->xingsBuf->getLastPos()>=1) {
            RTWaveSetPlayerTriggered_playNextWS(unit);
        }

        // play WaveSet
        if(unit->wsp.left()>0) {
            out[i] = unit->audioBuf->get(unit->wsp.next());
        }
        else{
            out[i] = 0.0;
        }
    }

}

void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Dtor(unit);
}

void RTWaveSetPlayerTriggered_playNextWS(RTWaveSetPlayerTriggered *unit){
    if(unit->trigIdx>0)
    {
        static WaveSet ws;

        if(unit->trigIdx != unit->oldTrigIdx)
        {
            ws = RTWaveSetPlayer_latesWSinRange(unit,minWavesetLength,maxWavesetLength);
            unit->oldTrigIdx = unit->trigIdx;
        }

        unit->wsp.playWS(ws,1,1);
    }
}
