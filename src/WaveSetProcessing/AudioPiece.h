#ifndef AUDIOPIECE_H
#define AUDIOPIECE_H

class AudioPiece
{

public:
    virtual ~AudioPiece(){}
    virtual int getLen()=0;
    virtual float getSample(int pos)=0;
    virtual float getSampleInterpolated(double pos)=0;

};

#endif // AUDIOPIECE_H
