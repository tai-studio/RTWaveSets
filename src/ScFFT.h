#ifndef SCFFT_H
#define SCFFT_H

#include "ScObject.h"
#include <complex>

class ScFFT : public ScObject
{
private:
    struct scfft *scfft;
    SCWorld_Allocator alloc;

public:

    enum Direction
    {
        kForward = 1,
        kBackward = 0
    };

    // These values are referred to from SC lang as well as in the following code - do not rearrange!
    enum WindowFunction
    {
        kRectWindow = -1,
        kSineWindow = 0,
        kHannWindow = 1
    };

    ScFFT(size_t fullsize, size_t winsize, WindowFunction wintype,
          float *indata, std::complex<float> *outdata, Direction forward=kForward);


    void calc();
    ~ScFFT();
};

#endif // SCFFT_H
