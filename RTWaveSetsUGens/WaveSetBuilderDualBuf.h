#ifndef WAVESETBUILDERDUALBUF_H
#define WAVESETBUILDERDUALBUF_H

#include "WaveSetBuilder.h"
#include "WsStorageDualBuf.h"

class WaveSetBuilderDualBuf : public WaveSetBuilder
{
private:
    /** Pointer to waveset storage */
    WsStorageDualBuf* wsData;

    /** Start idx of building waveset in the audio buffer */
    int startPos;

    float calcRMS(int start, int end);
public:

    WaveSetBuilderDualBuf(WsStorageDualBuf* wsData);
    virtual void startNewWaveSet();
    virtual void addAudio(float val);
    virtual int getRunningLegnth();
    virtual void saveAndStartNew();
};

#endif // WAVESETBUILDERDUALBUF_H
