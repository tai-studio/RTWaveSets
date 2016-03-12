#ifndef WAVESETBUILDERDUALBUF_H
#define WAVESETBUILDERDUALBUF_H

#include "WaveSetProcessing/WaveSetBuilder.h"
#include "WsStorageDualBuf.h"
#include "ScObject.h"

class WaveSetBuilderDualBuf : public WaveSetBuilder, public ScObject
{
private:
    /** Pointer to waveset storage */
    WsStorageDualBuf* wsData;

    /** Start idx of building waveset in the audio buffer */
    int startPos;

public:

    WaveSetBuilderDualBuf(WsStorageDualBuf* wsData);
    virtual void startNewWaveSet();
    virtual void addAudio(float val);
    virtual int getRunningLegnth();
    virtual void saveAndStartNew();
};

#endif // WAVESETBUILDERDUALBUF_H
