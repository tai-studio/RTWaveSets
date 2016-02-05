#include "RTWaveSetBase.h"


void RTWaveSetBase_Ctor(RTWaveSetBase *unit)
{
    unit->audioBuf = RTWaveSetBase_createRingBufferInBuffer<float>(ZIN0(0),unit); //FloatRingBuffer::createInBuffer(ZIN0(0),unit);
    unit->wsBuf = RTWaveSetBase_createRingBufferInBuffer<WaveSet>(ZIN0(1),unit);
}


/**
 * @brief Create a RingBuffer in the memory of a given sc-buffer. If not yet done it will be initialized.
 * Int the beginning of the memory a magic float value is stored to determine if the buffer is already initialized.
 * The Layout in the Buffer is: float firstMagicFloat, RingBuffer<T>, ringBufferData<T>[]
 * @param fbufnum
 * @param unit
 * @return
 */

template <typename T>
RingBuffer<T>* RTWaveSetBase_createRingBufferInBuffer(float fbufnum, Unit *unit)
{
    SndBuf* buf = RTWaveSetBase_getSndBuf(fbufnum,unit);
    float* data = (float*) buf->data;
    int dataSize = buf->samples*sizeof(float);

    // layout of the Buffer content: float firstMagicFloat, RingBuffer<T>,

    float* firstMagicFloat = data; // magic number at the Beginning of the Buffer to see if it's initialized
    RingBuffer<T>* srb = ( RingBuffer<T>*) (data+1);
    T* bufferContent = (T*) (srb+1);
    int bufferLen = (dataSize - sizeof(float) - sizeof( RingBuffer<T>))/sizeof(T);
    float magicValue = (bufferLen+fbufnum) * M_PI;

    // initialze the ringbuffer if not yet happend
    if(*firstMagicFloat!=magicValue){ // check magic number at the beginning of the buffer
        *firstMagicFloat=magicValue;
        *srb =  RingBuffer<T>((T*) bufferContent,bufferLen);
    }

    return srb;
}

/**
 * @brief Get a sound buffer from a given bufnum.
 * @param fbufnum
 * @param unit
 * @return pointer to the SndBuf.
 */

SndBuf* RTWaveSetBase_getSndBuf(float fbufnum, Unit* unit)
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
