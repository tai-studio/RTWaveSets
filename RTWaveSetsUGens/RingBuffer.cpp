#include "RingBuffer.h"
// #define RingBufferBuffer_DEBUG

#ifndef RINGBUFFER_CPP
#define RINGBUFFER_CPP


template <typename T>
RingBuffer<T>::RingBuffer(T* data, int len) {
    this->data = data;
    this->len = len;
    this->lastPos = -1;
}

template <typename T>
void RingBuffer<T>::put(T val) {
    lastPos++;
    this->data[lastPos % len] = val;
}

template <typename T>
T RingBuffer<T>::get(int getPos) {
    if(getPos <= (lastPos - len) || getPos > lastPos){
        printf("RingBuffer::get(%i) Error: Value out of Range! (len=%i,writePos=%i)\n",getPos,this->len,this->lastPos);
        return NAN;
    }

    return data[getPos % len];
}

template <typename T>
void RingBuffer<T>::set(int setPos, T val) {
    this->data[setPos % len] = val;
}

/**
 * @brief RingBufferBuffer::createInBuffer Creates a RingBufferBuffer in the memory of a given Buffer. The RingBufferBuffer object is placed in the beginning of the data, the BufferContent afterwards.
 * @param fbufnum
 * @param unit
 * @return
 */

template <typename T>
RingBuffer<T>*  RingBuffer<T>::createInBuffer(float fbufnum, Unit *unit)
{
    SndBuf* buf = getSndBuf(fbufnum,unit);
    void* data = (void*) buf->data;
    int dataSize = buf->samples*sizeof(float);

    // first put the RingBufferBuffer, afterwards the buffer content
    RingBuffer* srb = (RingBuffer*) data;
    T* bufferContent = (T*) (srb+1);
    int bufferLen = (dataSize - sizeof(RingBuffer))/sizeof(T);

    #ifdef RingBufferBuffer_DEBUG
    printf("RingBufferBuffer::createInBuffer() bufferLen=%i\n",bufferLen);
    #endif

    *srb = RingBuffer((T*) bufferContent,bufferLen);
    return srb;
}

template <typename T>
RingBuffer<T>*  RingBuffer<T>::getFromBuffer(float fbufnum, Unit *unit)
{
    SndBuf* buf = getSndBuf(fbufnum,unit);
    RingBuffer* srb = (RingBuffer*) buf->data;
    return srb;
}

template <typename T>
SndBuf* RingBuffer<T>::getSndBuf(float fbufnum, Unit* unit)
{
    SndBuf* buf;

    if (fbufnum < 0.f) { fbufnum = 0.f; }
    if (true){ //(fbufnum != unit->m_fbufnum) {
        uint32 bufnum = (int)fbufnum;
        World *world = unit->mWorld;
        if (bufnum >= world->mNumSndBufs) {
            int localBufNum = bufnum - world->mNumSndBufs;
            Graph *parent = unit->mParent;
            if(localBufNum <= parent->localBufNum) {
                buf = parent->mLocalSndBufs + localBufNum;
            } else {
                #ifdef RingBufferBuffer_DEBUG
                if(unit->mWorld->mVerbosity > -1){ 
                    printf("RingBufferBuffer::RingBufferBuffer error: invalid buffer number: %i.\n", bufnum);
                }
                #endif
                buf = NULL;
            }
        } else {
            buf = world->mSndBufs + bufnum;
        }

        if (!buf || !buf->data) {
            #ifdef RingBufferBuffer_DEBUG
            if(unit->mWorld->mVerbosity > -1){ 
                printf("RingBufferBuffer::RingBufferBuffer error: Buffer %i not initialised.\n", bufnum);
            }
            #endif
            buf = NULL;
        }
        //unit->m_fbufnum = fbufnum;
    }

    return buf;
}

#endif
