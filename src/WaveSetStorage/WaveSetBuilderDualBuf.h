#ifndef WAVESETBUILDERDUALBUF_H
#define WAVESETBUILDERDUALBUF_H

#include "WavesetProcessing/WavesetBuilder.h"
#include "WsStorageDualBuf.h"
#include "ScObject.h"

class WavesetBuilderDualBuf : public WavesetBuilder, public ScObject
{
private:
    /** Pointer to waveset storage */
    WsStorageDualBuf* wsData;

    /** Start idx of building waveset in the audio buffer */
    int startPos;

public:

    WavesetBuilderDualBuf(WsStorageDualBuf* wsData);
    virtual void startNewWaveset();
    virtual void addAudio(float val);
    virtual int getRunningLegnth();
    virtual void saveAndStartNew();
};

#endif // WAVESETBUILDERDUALBUF_H
