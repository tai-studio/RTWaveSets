#ifndef RTWAVESETSELECTOR_H
#define RTWAVESETSELECTOR_H

#include "RTWaveSetBase.h"

#define RTWaveSetSelector_xingLenBufferLen 100000

struct RTWaveSetSelector : public RTWaveSetBase  {
    float xingLenData[RTWaveSetSelector_xingLenBufferLen]; // TODO allocate dynamic depending on xingBuffer length
    //RingBufferBuffer xingLenBuffer;

    int searchIdx;
    int bestLen;
    int bestIdx;
    int desiredLen;
};

void RTWaveSetSelector_Ctor(RTWaveSetSelector *unit);
void RTWaveSetSelector_next(RTWaveSetSelector *unit, int inNumSamples);
void RTWaveSetSelector_Dtor(RTWaveSetSelector *unit);

#endif // RTWAVESETSELECTOR_H
