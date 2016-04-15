#include "SynthParallel.h"

SynthParallel::SynthParallel(WsStorage* wsData) : Synth(wsData)
{
    this->lastActiveIteratorIdx = -1;
}

/**
 * @brief Initiliazize a new parallel waveset playback.
 * The collected playbacks will be executed calling SynthParallel::getNextOutput().
 * @param wsIdx
 * @param groupSize
 * @param rate
 * @param repeat
 */

void SynthParallel::startNewPlayback(int wsIdx, int groupSize, float rate, int repeat)
{

    // We have a Trigger, get Waveset and set Iterator:
    // look for a free WavesetIterator
    for(int playIdx=0;playIdx<numPlayers;playIdx++)
    {
        WsPlayer* player = &this->wsPlayers[playIdx];
        if(player->endOfPlay()){
            // got a free Iterator: start Playback and exit loop

            this->initPlayback(player, (int) repeat,(int) groupSize,wsIdx ,rate);

            if(this->lastActiveIteratorIdx < playIdx){
                this->lastActiveIteratorIdx = playIdx;
            }

            break;
        }

        if(playIdx==numPlayers-1)
        {
            printf("SynthTriggered Warning: Max number of parallel Waveset playback exceeded!\n");
        }

    }

}

/**
 * @brief Get the next audio sample of the synthesis.
 * All parallel playbacks will be continued for one step and the outputs are summed up.
 * @return
 */

float SynthParallel::getNextOutput()
{

        // Play Wavesets from Iterators
        float outSum = 0.0;
        int lastPlayedIterator=-1;
        for(int playIdx=0;playIdx<=lastActiveIteratorIdx;playIdx++)
        {
            WsPlayer* player = &this->wsPlayers[playIdx];
            try
            {
                // play parallel Wavesets from Iterators
                if(!player->endOfPlay())
                {
                    outSum += player->nextSample();
                    lastPlayedIterator = playIdx;
                }
            }
            catch(...)
            {
                printf("Waveset playback failed! (unknown exception)\n");
                *player = WsPlayer(); // stop playback by resetting
            }
        }

        this->lastActiveIteratorIdx = lastPlayedIterator;


        return outSum;
}

