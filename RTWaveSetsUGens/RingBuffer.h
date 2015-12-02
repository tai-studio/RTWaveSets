#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "SC_PlugIn.h"



template <typename T>
class RingBuffer
{
private:
    T* data;
    int size;
    int firstPos;
    int lastPos;
public:
    RingBuffer(T* data, int size);
    void put(T val);
    void pop(){ setFirstPos(firstPos+1); }
    T get(int getPos);
    void set(int setPos, T val);
    T getLast(int back=0){ return get(lastPos-back); }
    T getFirst(int forward=0){ return get(firstPos+forward); }
    int getLastPos(){ return lastPos; }
    void setFirstPos(int firstPos);
    void validateFirstPos();
    int getFirstPos(){ return firstPos; }
    void setLastPos(int lastPos) {this->lastPos = lastPos; }
    int getSize() { return size; }
    int getLen(){ return lastPos - firstPos; }
    bool isInRange(int pos) { return (pos >= getFirstPos() && pos <= lastPos); }

    static SndBuf* getSndBuf(float fbufnum, Unit* unit);
    static RingBuffer<T>* createInBuffer(float bufnum, Unit* unit);
    static RingBuffer<T>* getFromBuffer(float fbufnum, Unit *unit);
};

#include "RingBuffer.cpp" // Implementation of template classes have to be available in the header

#endif // RINGBUFFER_H
