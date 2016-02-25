#include "SynthTriggered.h"

SynthTriggered::SynthTriggered(WsStorage* wsData) : Synth(wsData)
{
    this->lastActiveIteratorIdx = -1;
}

void SynthTriggered::startNewPlayback(int idxIn, int groupSize, float rate, int repeat)
{

    // We have a Trigger, get WaveSet and set Iterator:
    // look for a free WaveSetIterator
    for(int playIdx=0;playIdx<SynthTriggered_NumIterators;playIdx++)
    {
        WsPlayer* player = &this->wsIterators[playIdx];
        if(player->endOfPlay()){
            // got a free Iterator: start Playback and exit loop

            this->initPlayback(player, (int) repeat,(int) groupSize,idxIn ,rate);

            if(this->lastActiveIteratorIdx < playIdx){
                this->lastActiveIteratorIdx = playIdx;
            }

            break;
        }

        if(playIdx==SynthTriggered_NumIterators-1)
        {
            printf("SynthTriggered Warning: Max number of parallel WaveSet playback exceeded!\n");
        }

    }

}

float SynthTriggered::getNextOutput()
{

        // Play WaveSets from Iterators
        float outSum = 0.0;
        int lastPlayedIterator=-1;
        for(int playIdx=0;playIdx<=lastActiveIteratorIdx;playIdx++)
        {
            WsPlayer* player = &this->wsIterators[playIdx];
            try
            {
                // play parallel WaveSets from Iterators
                if(!player->endOfPlay())
                {
                    outSum += player->nextSample();
                    lastPlayedIterator = playIdx;
                }
            }
            catch(...)
            {
                printf("WaveSet playback failed! (unknown exception)\n");
                *player = WsPlayer(); // stop playback by resetting
            }
        }

        this->lastActiveIteratorIdx = lastPlayedIterator;


        return outSum;
}

