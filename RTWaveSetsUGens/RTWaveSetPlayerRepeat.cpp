#include "RTWaveSetPlayerRepeat.h"

void RTWaveSetPlayerRepeat_Ctor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Ctor(unit);
}

void RTWaveSetPlayerRepeat_next(RTWaveSetPlayerRepeat *unit, int inNumSamples){
    RTWaveSetPlayer_next(unit,inNumSamples);
}

void RTWaveSetPlayerRepeat_Dtor(RTWaveSetPlayerRepeat *unit){
    RTWaveSetPlayer_Dtor(unit);
}
