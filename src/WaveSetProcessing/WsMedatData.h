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

    WsMedatData() : rms(NAN), dur(NAN){}

    void calcMetadata(AudioPiece *audio);

private:
    float calcRMS(AudioPiece *audio);
    void calcFFT(AudioPiece *audio);
};

#endif // WSMEDATDATA_H
