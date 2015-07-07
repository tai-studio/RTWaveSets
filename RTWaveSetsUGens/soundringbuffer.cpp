#include "soundringbuffer.h"



SoundRingBuffer::SoundRingBuffer(float fbufnum, Unit* unit){
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

    //LOCK_SNDBUF(buf);


    // TODO warum funktioniert das nicht?
    // SoundRingBuffer(buf);

    this->sndBuf = buf;
    this->data = buf->data;
    this->len = buf->samples;
    this->lastPos = -1;


}

SoundRingBuffer::SoundRingBuffer(SndBuf *buf){
    this->sndBuf = buf;
    this->data = buf->data;
    this->len = buf->samples;
    this->lastPos = -1;
}

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
