#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "SC_PlugIn.h"

class SoundRingBuffer
{
private:
    SndBuf *sndBuf;
    float* data;
    int len;
    int lastPos;
public:
    SoundRingBuffer(float bufnum, Unit* unit);
    SoundRingBuffer(SndBuf *sndBuf);
    SoundRingBuffer(float* data, int len);
    void put(float val);
    float get(int getPos);
    void set(int setPos, float val);
    float getLast(int back=0){ return get(lastPos-back); }
    int getLastPos(){ return lastPos; }
    void setLastPos(int lastPos) {this->lastPos = lastPos; }
    int getLen() { return len; }
};

#endif // RINGBUFFER_H
