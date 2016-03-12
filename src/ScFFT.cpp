#include "ScFFT.h"
#include "FFT_UGens.h"


ScFFT::ScFFT(size_t fullsize, size_t winsize, WindowFunction wintype,
             float *indata, std::complex<float> *outdata, Direction forward):alloc(this->scInterface, this->scWorld)
{
    scfft = this->scInterface->fSCfftCreate(fullsize,winsize,(SCFFT_WindowFunction) wintype,indata,(float*)outdata,(SCFFT_Direction) forward,alloc);
}

void ScFFT::calc()
{
    this->scInterface->fSCfftDoFFT(scfft);
}

ScFFT::~ScFFT()
{
    this->scInterface->fSCfftDestroy(scfft,alloc);
}

