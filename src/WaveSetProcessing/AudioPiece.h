#ifndef AUDIOPIECE_H
#define AUDIOPIECE_H

#include "WaveSetStorage/WsStorageDualBuf.h"

class AudioPiece : public WsObject
{
private:
    WsStorageDualBuf* wsData;
    int start;
    int end;

public:


    int getStart(){ return start; }
    int getEnd(){ return end; }
    int getLen(){ return end-start; }

    AudioPiece();
    AudioPiece(WsStorageDualBuf* wsData,int start,int end);

    /** Threshold to do an Interpolation */
    static constexpr float interpThreshold = 0.01;
    float getSampleInterpolated(double pos);

};

#endif // AUDIOPIECE_H
