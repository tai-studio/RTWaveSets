#include "RingBuffer.h"
// #define RingBufferBuffer_DEBUG

#ifndef RINGBUFFER_CPP
#define RINGBUFFER_CPP


template <typename T>
RingBuffer<T>::RingBuffer(T* data, int size) {
    this->data = data;
    this->size = size;
    this->lastPos = -1;
    this->firstPos = -1;
}

template <typename T>
void RingBuffer<T>::put(T val) {
    lastPos++;

    validateFirstPos();

    this->data[lastPos % size] = val;
}

template <typename T>
void RingBuffer<T>::validateFirstPos(){

    // limit zero
    if(firstPos < 0 && lastPos >= 0) firstPos = 0;

    // limit to buffer capacity
    int minFirstPos = lastPos-size+1;
    if(firstPos < minFirstPos) firstPos = minFirstPos;

    // max limit is lastPos
    if(firstPos > lastPos) firstPos = lastPos+1;
}

template <typename T>
void RingBuffer<T>::setFirstPos(int firstPos){
    this->firstPos = firstPos;
    validateFirstPos();
}

template <typename T>
T RingBuffer<T>::get(int getPos) {
    if(getPos <= (lastPos - size) || getPos > lastPos){
        printf("RingBuffer::get(%i) Error: Value out of Range! (len=%i,writePos=%i)\n",getPos,this->size,this->lastPos);
        throw "Index Out of Range!";
    }

    return data[getPos % size];
}

template <typename T>
void RingBuffer<T>::set(int setPos, T val) {
    this->data[setPos % size] = val;
}

#endif
