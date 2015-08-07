#ifndef RTWaveSetPlayerTriggered_H
#define RTWaveSetPlayerTriggered_H

#include "RTWaveSetPlayer.h"


struct RTWaveSetPlayerTriggered : public RTWaveSetPlayer  {

    /** Previous Trigger Input */
    float prevTrig;

    /** xings Index of last Trigger **/
    int trigIdx;

    int oldTrigIdx;
};

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit);
void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples);
void RTWaveSetPlayerTriggered_playNextWS(RTWaveSetPlayerTriggered *unit);
void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit);

#endif // RTWaveSetPlayerTriggered_H
