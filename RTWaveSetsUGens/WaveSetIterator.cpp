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
 * @return Sample position in the buffer.
 */

int WaveSetIterator::next() {

    int val;
    // end of playback?
    if(repeat>=0) {
        val = (int) playPos;

        // printf("WaveSetPlayer::next(): playPos %lf \n", playPos);
        // printf("WaveSetPlayer::next(): val     %i \n", val);

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
        playPos = ws.start;
    } else {
        playPos = ws.end;
    }
}

/**
 * @brief Number of samples that are left in current playing waveset.
 * @return Number of samples left.
 */

int WaveSetIterator::left() {
    if(playRate==0) return 0;
    if(ws.start>=ws.end) return 0;

    // simplified Version 1/0:
    if(repeat<0) return 0;
    else return 1;

    // full Version (not working):
    /*if(playRate>0) { // forward
        return float(ws.end-playPos+1 + repeat*(ws.end-ws.start+1)) / fabsf(playRate);
    }else{ // backward
        return float(playPos-ws.start+1 + repeat*(ws.end-ws.start+1)) / fabsf(playRate);
    }*/



}
