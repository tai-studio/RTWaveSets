#include "Synth.h"

Synth::Synth(WsStorage* wsData) : wsData(wsData)
{

}

/**
 * @brief Fold a index out of range within the available range.
 * @param xingIdx
 * @return
 */

int Synth::foldIdx(int wsIdx){
    // fold idx if its out of range
     if(!wsData->isValidWsIdx(wsIdx)){

         // fold within available wavesets
         wsIdx = wsIdx % wsData->getNumWsInStorage();

         // shift in absolute buffer range
         while(wsIdx < wsData->getFirstWsIdx()) {
             wsIdx += wsData->getMaxWsCapacity();
         }

     }

     return wsIdx;
}

/**
 * @brief Get the Group and init playback.
 * @param player
 * @param repeat
 * @param groupSize
 * @param xingIdx
 * @param rate
 */

void Synth::initPlayback(WsPlayer *player, float repeat, int groupSize, int xingIdx, float rate)
{
    xingIdx = foldIdx(xingIdx);
    if(!wsData->isValidWsIdx(xingIdx)) throw "RTWavesetSynth_playNextWS() Error: Waveset idx out of range!";
    AudioPiece* ws = this->wsData->createGroup(xingIdx,groupSize);
    player->playWS(ws,repeat,rate);
}


// TODO move to AudioPiece
