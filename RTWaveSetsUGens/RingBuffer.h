#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "SC_PlugIn.h"



template <typename T>
class RingBuffer
{
private:
    T* data;
    int len;
    int lastPos;
public:
    RingBuffer(T* data, int len);
    void put(T val);
    T get(int getPos);
    void set(int setPos, T val);
    T getLast(int back=0){ return get(lastPos-back); }
    int getLastPos(){ return lastPos; }
    int getFirstPos(){ int firstPos = lastPos-len+1; if(firstPos<0) firstPos=0; return firstPos; }
    void setLastPos(int lastPos) {this->lastPos = lastPos; }
    int getLen() { return len; }
    bool isInRange(int pos) { return (pos >= getFirstPos() && pos <= lastPos); }

    static SndBuf* getSndBuf(float fbufnum, Unit* unit);
    static RingBuffer<T>* createInBuffer(float bufnum, Unit* unit);
    static RingBuffer<T>* getFromBuffer(float fbufnum, Unit *unit);
};

typedef RingBuffer<float> FloatRingBuffer;

#include "RingBuffer.cpp" // Implementation of template classes have to be available in the header

#endif // RINGBUFFER_H
