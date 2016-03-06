#ifndef AUDIOPIECE_H
#define AUDIOPIECE_H

#include "WaveSetStorage/WsStorageDualBuf.h"

class AudioPiece
{

public:
    virtual ~AudioPiece(){}
    virtual int getLen()=0;
    virtual float getSampleInterpolated(double pos)=0;

};

#endif // AUDIOPIECE_H
