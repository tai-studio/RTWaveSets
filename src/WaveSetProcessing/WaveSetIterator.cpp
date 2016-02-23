#include "WaveSetIterator.h"
//#define WaveSetIterator_DEBUG


/**
 * @brief WaveSetPlayer::WaveSetPlayer Constructor, just init values.
 */

WaveSetIterator::WaveSetIterator(){
    playPos = -1;
    ws.start = -1;
    ws.end = -1;
    repeat = -1;
    playRate = 1;
}


/**
 * @brief Get the position of the next Sample of the waveset.
 * @return Sample position in the buffer or -1 if end is reached.
 */

double WaveSetIterator::next() {

    double val;
    // end of playback?
    if(repeat>=0) {
        val = playPos;

        if(val < 0 || val >= INT32_MAX){
            printf("WaveSetPlayer::next(): Error! invalid playPos:%lf val:%f start:%i end:%i repeat:%i playRate:%f\n", playPos, val, ws.start, ws.end, repeat, playRate);
            val = -1;
            repeat = -1; // stop playback
        }

        playPos+=playRate;
    }
    else {
        #ifdef WaveSetIterator_DEBUG
        printf("WaveSetPlayer::next() reached End of Waveset!\n");
        #endif

        val=-1;
    }

    // next repeat? -> reset to start
    if(playRate > 0 && ((int)playPos) >= ws.end) // forward Playback
    {
        playPos = ws.start; // TODO add partial steps between? (playPos-ws.start)
        repeat--;
    }
    else if(playRate < 0 && ((int)playPos) <= ws.start) // backward Playback
    {
        playPos = ws.end;
        repeat--;
    }

    return val;
}


/**
 * @brief playWS
 * @param ws WaveSet to play.
 * @param repeat Number of repetitons (1..*).
 * @param step Step size for the playback (i.e. -1 for reverse oder 2 for double speed).
 */

void WaveSetIterator::playWS(WaveSetPlay ws, int repeat, float playRate){
    this->ws = ws;
    this->repeat = repeat-1;
    this->playRate = playRate;

    if(playRate>0) {
        playPos = (double) ws.start;
    } else {
        playPos = (double) ws.end;
    }
    #ifdef WaveSetIterator_DEBUG
    printf("WaveSetIterator::playWS(): start:%i end:%i repeat:%i playRate:%f\n", ws.start, ws.end, repeat, playRate);
    #endif

}

/**
 * @brief Returns true if reached the end of playback.
 */

bool WaveSetIterator::endOfPlay() {

    if(repeat<0) return true;
    if(playRate==0) return true;
    if(ws.start>=ws.end) return true;


    return false;
}
