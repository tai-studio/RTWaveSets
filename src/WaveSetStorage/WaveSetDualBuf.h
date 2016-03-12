#ifndef WaveSetDualBuf_H
#define WaveSetDualBuf_H

#include "RingBuffer.h"
#include "WaveSetProcessing/Waveset.h"
#include "ScObject.h"
#include "AudioPieceDualBuf.h"

class WaveSetDualBuf : public Waveset, public ScObject, public AudioPieceDualBuf {
public:

    struct Data{
    public:
        /**
         * @brief Idx of first sample in aduiobuffer.
         */
        int start;

        /**
         * @brief idx of last sample in audiobuffer.
         */
        int end;

        /**
         * @brief RMS of the WaveSet.
         */
        float rms;
    };

    Data data;


    WaveSetDualBuf(WsStorageDualBuf *wsData,int start, int end, float amp) : AudioPieceDualBuf(wsData,start,end){
        this->data.start = start;
        this->data.end = end;
        this->data.rms = amp;
    }

    WaveSetDualBuf(WsStorageDualBuf *wsData, WaveSetDualBuf::Data data) : data(data) , AudioPieceDualBuf(wsData,data.start,data.end){
    }


    /**
     * @brief Length of the WaveSet in samples.
     * @return
     */
    virtual int getLength() { return this->data.end-this->data.start; }


    /**
     * @brief get the value of the rms feature.
     * @return
     */
    virtual float getRMS(){ return this->data.rms; }



};

#endif // WAVESET_H
