#include "WaveSetBuilderDualBuf.h"
#include "ScFFT.h"
#include <complex.h>

/**
 * @brief Constructor.
 * @param wsData
 */

WaveSetBuilderDualBuf::WaveSetBuilderDualBuf(WsStorageDualBuf* wsData)
{
    this->wsData = wsData;
    this->startPos = INT32_MAX;
}


/**
 * @brief Start a new waveset, save current audio position.
 */

void WaveSetBuilderDualBuf::startNewWaveSet()
{
    startPos = wsData->audioBuf->getLastPos();
}


/**
 * @brief WaveSetBuilderDualBuf::addAudio
 * @param val
 */

void WaveSetBuilderDualBuf::addAudio(float val)
{
    wsData->audioBuf->put(val);
    wsData->cleanUp();
}


/**
 * @brief Get the current length of the currently building waveset.
 * @return length of the WS or -1 if there is no valid WS started.
 */

int WaveSetBuilderDualBuf::getRunningLegnth()
{
    if(wsData->audioBuf->isInRange(startPos)){
        return wsData->audioBuf->getLastPos() - startPos;
    }
    else {
        return -1;
    }
}


/**
 * @brief close the waveset and save it to the storage.
 */

void WaveSetBuilderDualBuf::saveAndStartNew()
{

    if(wsData->audioBuf->isInRange(startPos)){
        int endPos = wsData->audioBuf->getLastPos();
        WaveSetDualBuf ws(wsData,startPos,endPos,-1);

        float rms = calcRMS(&ws);
        ws.data.rms = rms;

        calcFFT(&ws);

        wsData->wsBuf->put(ws.data);
    }

    this->startNewWaveSet();
}

/**
 * @brief Calculate the RMS of a waveset signal.
 * @param start
 * @param end
 * @return
 */

float WaveSetBuilderDualBuf::calcRMS(AudioPiece* audio){
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

void WaveSetBuilderDualBuf::calcFFT(AudioPiece *audio)
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
