#include "RTWaveSetPlayerTriggered.h"

void RTWaveSetPlayerTriggered_Ctor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Ctor(unit);
    unit->prevTrig = 1.0;

    // init WaveSetIterators
    for(int i=0;i<RTWaveSetPlayerTriggered_NumIterators;i++)
    {
        unit->wsIterators[i] = WsPlayer();
    }
    unit->lastActiveIteratorIdx = -1;

    SETCALC(RTWaveSetPlayerTriggered_next);
    RTWaveSetPlayerTriggered_next(unit, 1);
}


/**
 * @brief Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetPlayerTriggered_next(RTWaveSetPlayerTriggered *unit, int inNumSamples){

    // ^this.multiNew('audio', audioBuf, wsBuf, trig, idx, rate, groupSize, repeat)

    // Inputs:
    float *trig = IN(2);
    float *idxInFloat = IN(3);
    float rate = IN0(4);
    float groupSize = IN0(5);
    float repeat = IN0(6);
    // Outputs:
    float *out = OUT(0);

    // WaveSet Playback
    for ( int i=0; i<inNumSamples; ++i) {

        // get Index Input
        int idxIn = (int) idxInFloat[i];

        // check for Trigger and valid idx input
        if(trig[i]>0.0 && unit->prevTrig<=0.0 && idxIn >= 0)
        {
            // We have a Trigger, get WaveSet and set Iterator:
            // look for a free WaveSetIterator
            for(int playIdx=0;playIdx<RTWaveSetPlayerTriggered_NumIterators;playIdx++)
            {
                WsPlayer* wsi = &unit->wsIterators[playIdx];
                if(wsi->endOfPlay()){
                    // got a free Iterator: start Playback and exit loop

                    RTWaveSetPlayer_playGroup(wsi, unit,(int) repeat,(int) groupSize,idxIn ,rate);
                    if(unit->lastActiveIteratorIdx < playIdx){
                        unit->lastActiveIteratorIdx = playIdx;
                    }

                    break;
                }

                if(playIdx==RTWaveSetPlayerTriggered_NumIterators-1)
                {
                    printf("RTWaveSetPlayerTriggered Warning: Number of parallel WaveSet playback exceeded!\n");
                }

            }

        }

        // Play WaveSets from Iterators
        float outSum = 0.0;
        int lastPlayedIterator=-1;
        for(int playIdx=0;playIdx<=unit->lastActiveIteratorIdx;playIdx++)
        {
            WsPlayer* wsi = &unit->wsIterators[playIdx];
            try
            {
                // play parallel WaveSets from Iterators
                if(!wsi->endOfPlay())
                {
                        double idx = wsi->next();
                        if(unit->wsData.audioBuf->isInRange((int)idx)) {
                            outSum += RTWaveSetPlayer_getSample(unit,idx);
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
        out[i] = outSum;

        unit->prevTrig=trig[i];
        unit->lastActiveIteratorIdx = lastPlayedIterator;
    }


}


void RTWaveSetPlayerTriggered_Dtor(RTWaveSetPlayerTriggered *unit){
    RTWaveSetPlayer_Dtor(unit);
}
