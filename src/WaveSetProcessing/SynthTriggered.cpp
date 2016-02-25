#include "SynthTriggered.h"

SynthTriggered::SynthTriggered(WsStorage* wsData)
{
    this->wsData = (WsStorageDualBuf*) wsData;
    this->lastActiveIteratorIdx = -1;
}

void SynthTriggered::startNewPlayback(int idxIn, int groupSize, float rate, int repeat)
{

    // We have a Trigger, get WaveSet and set Iterator:
    // look for a free WaveSetIterator
    for(int playIdx=0;playIdx<SynthTriggered_NumIterators;playIdx++)
    {
        WsPlayer* wsi = &this->wsIterators[playIdx];
        if(wsi->endOfPlay()){
            // got a free Iterator: start Playback and exit loop

            this->playGroup(wsi, (int) repeat,(int) groupSize,idxIn ,rate);

            if(this->lastActiveIteratorIdx < playIdx){
                this->lastActiveIteratorIdx = playIdx;
            }

            break;
        }

        if(playIdx==SynthTriggered_NumIterators-1)
        {
            printf("RTWaveSetPlayerTriggered Warning: Number of parallel WaveSet playback exceeded!\n");
        }

    }

}

float SynthTriggered::getNextOutput()
{

        // Play WaveSets from Iterators
        float outSum = 0.0;
        int lastPlayedIterator=-1;
        for(int playIdx=0;playIdx<=this->lastActiveIteratorIdx;playIdx++)
        {
            WsPlayer* wsi = &this->wsIterators[playIdx];
            try
            {
                // play parallel WaveSets from Iterators
                if(!wsi->endOfPlay())
                {
                        double idx = wsi->next();
                        if(this->wsData->audioBuf->isInRange((int)idx)) {
                            outSum += this->getSampleInterpolated(idx);
                            lastPlayedIterator = playIdx;
                        } else {
                            printf("WaveSet playback failed! (out of audio buffer Range)\n");
                            *wsi = WsPlayer(); // stop playback by resetting
                        }
                }
            }
            catch(...)
            {
                printf("WaveSet playback failed! (unknown exception)\n");
                *wsi = WsPlayer(); // stop playback by resetting
            }
        }
        this->lastActiveIteratorIdx = lastPlayedIterator;

        return outSum;
}

