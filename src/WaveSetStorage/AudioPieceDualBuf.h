#ifndef AUDIOPIECEDUALBUF_H
#define AUDIOPIECEDUALBUF_H

#include "WavesetProcessing/AudioPiece.h"

class WsStorageDualBuf;

class AudioPieceDualBuf : public AudioPiece
{  

private:
    WsStorageDualBuf* wsData;
    int start;
    int end;

public:

    int getStart(){ return start; }
    int getEnd(){ return end; }
    int getLen(){ return end-start; }

    AudioPieceDualBuf(WsStorageDualBuf* wsData,int start,int end);

    /** Threshold to do an Interpolation */
    static constexpr float interpThreshold = 0.01;
    virtual float getSample(int pos);
    float getSampleInterpolated(double pos);

};

#endif // AUDIOPIECEDUALBUF_H
