#include "WsStorageDualBuf.h"
#include "WavesetBuilderDualBuf.h"
#include "WavesetProcessing/AudioPiece.h"
#include "AudioPieceDualBuf.h"

/**
 * @brief Create waveset data structure in given sc-buffers.
 * @param fbufnumAudio
 * @param fbufnumWS
 * @param unit
 */

WsStorageDualBuf::WsStorageDualBuf(float fbufnumAudio, float fbufnumWS, Unit *unit)
{
    this->audioBuf = createRingBufferInBuffer<float>(fbufnumAudio,unit);
    this->wsBuf = createRingBufferInBuffer<WavesetDualBuf::Data>(fbufnumWS,unit);
}

/**
 * @brief Simple constructor for existing buffers.
 * @param audioBuf
 * @param wsBuf
 */

WsStorageDualBuf::WsStorageDualBuf(FloatRingBuffer *audioBuf, WavesetRingBuffer *wsBuf)
{
    this->audioBuf = audioBuf;
    this->wsBuf = wsBuf;
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
RingBuffer<T> *WsStorageDualBuf::createRingBufferInBuffer(float fbufnum, Unit *unit)
{
    SndBuf* buf = WavesetBase_getSndBuf(fbufnum,unit);
    if(buf==NULL) throw "no valid buffer!";

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
        *srb = RingBuffer<T>((T*) bufferContent,bufferLen);
    }

    return srb;
}

/**
 * @brief Get a sound buffer from a given bufnum.
 * @param fbufnum
 * @param unit
 * @return pointer to the SndBuf.
 */

SndBuf *WsStorageDualBuf::WavesetBase_getSndBuf(float fbufnum, Unit *unit)
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

/**
 * @brief Get a new instance of the waveset builder.
 * The instance will be allocated dynamically and have to be deleted if its not used anymore.
 * @return
 */

WavesetBuilder* WsStorageDualBuf::createWavesetBuilder()
{
    return new WavesetBuilderDualBuf(this);
}

/**
 * @brief Remove obsolete wavesets
 */

void WsStorageDualBuf::cleanUp()
{
    if(wsBuf->getLen()>0){
        while(! audioBuf->isInRange(wsBuf->getFirst().start) || ! audioBuf->isInRange(wsBuf->getFirst().end)) // remove wavesets out of audio range
        {
            wsBuf->pop();
        }
    }
}


/**
 * @brief Get a group.
 * @param wsIdx
 * @param groupSize
 * @return
 */
AudioPiece* WsStorageDualBuf::createGroup(int wsIdx, int groupSize){

    if(groupSize < 1) groupSize = 1;

    AudioPiece* ws = NULL;

    if(this->wsBuf->isInRange(wsIdx) && groupSize<this->wsBuf->getLen())
    {
        int startIdx = wsIdx-groupSize/2;
        int endIdx = startIdx + groupSize - 1;

        // shift back if we are at the end
        if(endIdx>this->wsBuf->getLastPos())
        {
            endIdx = this->wsBuf->getLastPos();
            startIdx = endIdx - groupSize + 1;
        }

        // shift forward if we are on the beginning
        if(startIdx<this->wsBuf->getFirstPos()){
            startIdx = this->wsBuf->getFirstPos();
            endIdx = startIdx + groupSize - 1;
        }

        int start = this->wsBuf->get(startIdx).start;
        int end = this->wsBuf->get(endIdx).end;

        if(isnan(end) || isnan(start) || end<1 || start<0)
        {
            printf("RTWavesetSynth Warning: no valid Waveset found in xing Buffer!\n");
            return NULL;
        }

        ws = new AudioPieceDualBuf(this,start,end);
    }

    return ws;
}
