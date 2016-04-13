#ifndef WSMEDATDATA_H
#define WSMEDATDATA_H

#include "AudioPiece.h"

#include <math.h>

/**
 * @brief Store and calculate waveset metadata.
 */

class WsMedatData
{
public:
    float rms;
    float dur;
    int peaks;

    WsMedatData() : rms(NAN), dur(NAN), peaks(-1){}

    void calcMetadata(AudioPiece *audio);

private:
    float calcRMS(AudioPiece *audio);
    void calcFFT(AudioPiece *audio);
    int calcPeaks(AudioPiece *audio);
    float calcDur(AudioPiece *audio);
};

#endif // WSMEDATDATA_H
