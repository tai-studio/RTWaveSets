#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "SC_PlugIn.h"

class SoundRingBuffer
{
private:
    float* data;
    int len;
    int lastPos;
public:
    SoundRingBuffer(float* data, int len);
    void put(float val);
    float get(int getPos);
    void set(int setPos, float val);
    float getLast(int back=0){ return get(lastPos-back); }
    int getLastPos(){ return lastPos; }
    void setLastPos(int lastPos) {this->lastPos = lastPos; }
    int getLen() { return len; }

    static SndBuf* getSndBuf(float fbufnum, Unit* unit);
    static SoundRingBuffer* createInBuffer(float bufnum, Unit* unit);
    static SoundRingBuffer* getFromBuffer(float fbufnum, Unit *unit);
};

#endif // RINGBUFFER_H
