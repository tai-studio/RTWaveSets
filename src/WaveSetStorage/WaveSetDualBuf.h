#ifndef WAVESET_H
#define WAVESET_H

#include "RingBuffer.h"

class WaveSetDualBuf {
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

};

#endif // WAVESET_H
