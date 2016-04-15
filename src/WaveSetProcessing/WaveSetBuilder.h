#ifndef WAVESETBUILDER_H
#define WAVESETBUILDER_H

#include "ScObject.h"

class WavesetBuilder
{
public:
    virtual ~WavesetBuilder(){}
    virtual void startNewWaveset()=0;
    virtual void addAudio(float val)=0;
    virtual int getRunningLegnth()=0;
    virtual void saveAndStartNew()=0;
};

#endif // WAVESETBUILDER_H
