#ifndef WaveSetDualBuf_H
#define WaveSetDualBuf_H

#include "RingBuffer.h"
#include "WaveSetProcessing/Waveset.h"
#include "WsObject.h"

class WaveSetDualBuf : public Waveset, public WsObject {
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


    WaveSetDualBuf(int start, int end, float amp){
        this->data.start = start;
        this->data.end = end;
        this->data.rms = amp;
    }

    WaveSetDualBuf(WaveSetDualBuf::Data data) : data(data){
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
