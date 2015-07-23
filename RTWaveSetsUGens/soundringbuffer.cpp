#include "SoundRingBuffer.h"

SoundRingBuffer::SoundRingBuffer(float* data, int len) {
    this->data = data;
    this->len = len;
    this->lastPos = -1;
}

void SoundRingBuffer::put(float val) {
    lastPos++;
    this->data[lastPos % len] = val;
}

float SoundRingBuffer::get(int getPos) {
    if(getPos <= (lastPos - len) || getPos > lastPos){
        printf("RingBuffer::get(%i) Error: Value out of Range! (len=%i,writePos=%i)\n",getPos,this->len,this->lastPos);
        return NAN;
    }

    return data[getPos % len];
}

void SoundRingBuffer::set(int setPos, float val) {
    this->data[setPos % len] = val;
}

/**
 * @brief SoundRingBuffer::createInBuffer Creates a SoundRingBuffer in the memory of a given Buffer. The SoundringBuffer object is placed in the beginning of the data, the BufferContent afterwards.
 * @param fbufnum
 * @param unit
 * @return
 */

SoundRingBuffer*  SoundRingBuffer::createInBuffer(float fbufnum, Unit *unit)
{
    SndBuf* buf = getSndBuf(fbufnum,unit);
    void* data = (void*) buf->data;
    int dataSize = buf->samples*sizeof(float);

    // first put the SoundRingBuffer, afterwards the buffer content
    SoundRingBuffer* srb = (SoundRingBuffer*) data;
    float* bufferContent = (float*) (srb+1);
    int bufferLen = (dataSize - sizeof(SoundRingBuffer))/sizeof(float);

    printf("SoundRingBuffer::createInBuffer() bufferLen=%i\n",bufferLen);

    *srb = SoundRingBuffer((float*) bufferContent,bufferLen);
    return srb;
}

SoundRingBuffer*  SoundRingBuffer::getFromBuffer(float fbufnum, Unit *unit)
{
    SndBuf* buf = getSndBuf(fbufnum,unit);
    SoundRingBuffer* srb = (SoundRingBuffer*) buf->data;
    return srb;
}

SndBuf* SoundRingBuffer::getSndBuf(float fbufnum, Unit* unit)
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
            } else { \
                if(unit->mWorld->mVerbosity > -1){ printf("SoundRingBuffer::SoundRingBuffer error: invalid buffer number: %i.\n", bufnum); }
                buf = NULL;
            }
        } else {
            buf = world->mSndBufs + bufnum;
        }

        if (!buf || !buf->data) {
            if(unit->mWorld->mVerbosity > -1){ printf("SoundRingBuffer::SoundRingBuffer error: Buffer %i not initialised.\n", bufnum); }
            buf = NULL;
        }
        //unit->m_fbufnum = fbufnum;
    }

    return buf;
}
