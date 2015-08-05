#include "RTWaveSetPlayerTriggered.h"

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Ctor(unit);
}

void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples){
    RTWaveSetPlayer_next(unit,inNumSamples);
}

void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Dtor(unit);
}
