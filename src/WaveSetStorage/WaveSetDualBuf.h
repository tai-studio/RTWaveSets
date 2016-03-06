#ifndef WaveSetDualBuf_H
#define WaveSetDualBuf_H

#include "RingBuffer.h"
#include "WaveSetProcessing/Waveset.h"
#include "WsObject.h"

class WaveSetDualBuf : public Waveset, public WsObject {
public:
    WaveSetDualBuf(int start, int end, float amp){
        this->start = start;
        this->end = end;
        this->rms = amp;
    }

    /**
     * @brief Length of the WaveSet in samples.
     * @return
     */
    int getLength() { return end-start; }

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

    /**
     * @brief get the value of the rms feature.
     * @return
     */
    float getRMS(){ return rms; }

};

#endif // WAVESET_H
