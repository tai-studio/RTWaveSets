#ifndef WAVESETBUILDER_H
#define WAVESETBUILDER_H

class WaveSetBuilder
{
public:
    virtual void startNewWaveSet()=0;
    virtual void addAudio(float val)=0;
    virtual int getRunningLegnth()=0;
    virtual void saveAndStartNew()=0;
};

#endif // WAVESETBUILDER_H
