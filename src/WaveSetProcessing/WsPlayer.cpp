#include "WsPlayer.h"
//#define WsPlayer_DEBUG


/**
 * @brief WaveSetPlayer::WaveSetPlayer Constructor, just init values.
 */

WsPlayer::WsPlayer() {
    playPos = -1;
    repeat = -1;
    playRate = 1;
}


/**
 * @brief Get the position of the next Sample of the waveset.
 * @return Sample position in the buffer or -1 if end is reached.
 */

double WsPlayer::nextPos() {

    double val;
    // end of playback?
    if(repeat>=0) {
        val = playPos;

        if(val < 0 || val >= INT32_MAX){
            printf("WaveSetPlayer::next(): Error! invalid playPos");
            val = -1;
            repeat = -1; // stop playback
        }

        playPos+=playRate;
    }
    else {
        // reached end
        val=-1;
    }

    // next repeat? -> reset to start
    if(playRate > 0 && ((int)playPos) >= ws.getLen()) // forward Playback // TODO müsste das nicht len-1 sein?
    {
        playPos = 0; // TODO add partial steps between? (playPos-ws.getStart())
        repeat--;
    }
    else if(playRate < 0 && ((int)playPos) <= 0.0) // backward Playback
    {
        playPos = ws.getLen();
        repeat--;
    }

    return val;
}

float WsPlayer::nextSample()
{
    return this->ws.getSampleInterpolated(nextPos());
}


/**
 * @brief playWS
 * @param ws WaveSet to play.
 * @param repeat Number of repetitons (1..*).
 * @param step Step size for the playback (i.e. -1 for reverse oder 2 for double speed).
 */

void WsPlayer::playWS(AudioPiece ws, int repeat, float playRate){
    this->ws = ws;
    this->repeat = repeat-1;
    this->playRate = playRate;

    if(playRate>0) {
        playPos = 0;
    } else {
        playPos = ws.getLen();
    }

    // TODO playback including or excluding "end" sample?
}

/**
 * @brief Returns true if reached the end of playback.
 */

bool WsPlayer::endOfPlay() {

    if(repeat<0) return true;
    if(playRate==0) return true;
    if(ws.getStart()>=ws.getEnd()) return true;

    return false;
}
