#include "WaveSetIterator.h"
// #define WaveSetIterator_DEBUG
/**
 * @brief WaveSetPlayer::WaveSetPlayer Constructor, just init values.
 */

WaveSetIterator::WaveSetIterator(){
    playPos = -1;
    ws.start = -1;
    ws.end = -1;
    repeat = 0;
    step = 1;
}


/**
 * @brief Get the position of the next Sample of the waveset.
 * @return Sample position in the buffer.
 */

int WaveSetIterator::next() {
    if(playPos*playDir >= ws.end*playDir && repeat > 0){
        playPos = ws.start;
        repeat--;
    }

    if(playPos*playDir < ws.end*playDir) {
        int val = playPos;
        playPos+=step;
        return val;
    } else {
        #ifdef WaveSetIterator_DEBUG
        printf("WaveSetPlayer::next() reached End of Waveset!\n");
        #endif
        
        return -1;
    }
}


/**
 * @brief playWS
 * @param ws WaveSet to play.
 * @param repeat Number of repetitons (1..*).
 * @param step Step size for the playback (i.e. -1 for reverse oder 2 for double speed).
 */

void WaveSetIterator::playWS(WaveSet ws, int repeat, int step){
    this->ws = ws;
    this->repeat = repeat-1;
    this->step = step;
    this->playDir = step/abs(step);
    playPos = ws.start;
}

/**
 * @brief Number of samples that are left in current playing waveset.
 * @return Number of samples left.
 */

int WaveSetIterator::left() {
    return (ws.end-playPos-playDir)/step + (repeat*(ws.end-ws.start-playDir))/step;
}
