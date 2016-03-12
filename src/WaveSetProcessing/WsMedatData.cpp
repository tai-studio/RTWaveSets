#include "WsMedatData.h"
#include "ScFFT.h"

/**
 * @brief Calculate all metadata using the given audio piece.
 * @param audio
 */

void WsMedatData::calcMetadata(AudioPiece *audio)
{
    rms=calcRMS(audio);
    // TODO calc duration
    //calcFFT(audio);
}

/**
 * @brief Calculate the RMS of a waveset signal.
 * @param start
 * @param end
 * @return
 */

float WsMedatData::calcRMS(AudioPiece* audio){
    float rms = 0.0;

    int len = audio->getLen();
    for(int pos=0;pos<len;pos++)
    {
        float val = audio->getSample(pos);
        rms += val*val;
    }

    rms = sqrtf(rms / audio->getLen());
    return rms;
}

void WsMedatData::calcFFT(AudioPiece *audio)
{
    static constexpr int fftSize = 1024;
    static float fftIn[fftSize];
    std::complex<float> fftOut[fftSize/2];

    // fill signal buffer by repeating waveset
    int pos = 0;
    int audioLen = audio->getLen();
    for(int idx=0;idx<fftSize;idx++){
        if(pos>=audioLen) pos = 0;
        fftIn[idx]=audio->getSample(pos);
        pos++;
    }

    ScFFT fft = ScFFT(fftSize,fftSize,ScFFT::kHannWindow,fftIn,fftOut);
    fft.calc();

    //SCComplexBuf* fftResult = (SCComplexBuf*) &fftout;
    int numbins = (fftSize) >> 1;

    // find max FFT value
    float max = 0.0;
    int maxIdx;
    for(int idx=1;idx<numbins;idx++){
        //Complex bin = fftResult->bin[idx];
        std::complex<float> bin = fftOut[idx];
        float abs = std::norm(bin);

        if(abs>max){
            max = abs;
            maxIdx = idx;
        }

    }


    // print result
    static int cnt = 0;
    cnt++;
    if(cnt==1000) {
        cnt=0;
        float freq = (44100.0 / fftSize) * maxIdx;
        printf("max FFT bin: %i of %i f=%f\n",maxIdx+1,numbins,freq);
        printf("FFT bin %f\n",fftOut[numbins].real());

        // bin 10 is equal to 430,66 Hz

    }
}
