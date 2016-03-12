#ifndef WaveSetDualBuf_H
#define WaveSetDualBuf_H

#include "RingBuffer.h"
#include "WaveSetProcessing/Waveset.h"
#include "ScObject.h"
#include "AudioPieceDualBuf.h"
#include "WaveSetProcessing/WsMedatData.h"

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

        WsMedatData metaData;
    };

    Data data;

    WaveSetDualBuf(WsStorageDualBuf *wsData,int start, int end) : AudioPieceDualBuf(wsData,start,end){
        this->data.start = start;
        this->data.end = end;
    }

    WaveSetDualBuf(WsStorageDualBuf *wsData, WaveSetDualBuf::Data data) : data(data) , AudioPieceDualBuf(wsData,data.start,data.end){
    }

    void calcMetaData()
    {
        this->data.metaData.calcMetadata(this);
    }

    /**
     * @brief Length of the WaveSet in samples.
     * @return
     */
    virtual int getLength() { return this->data.end-this->data.start; } // TODO replace by getMetadata


    /**
     * @brief get the value of the rms feature.
     * @return
     */
    virtual WsMedatData getMetaData(){ return this->data.metaData; }



};

#endif // WAVESET_H
