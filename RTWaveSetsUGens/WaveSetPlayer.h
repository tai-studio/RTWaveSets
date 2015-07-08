#ifndef WAVESET_H
#define WAVESET_H

#include "SC_PlugIn.h"

struct WaveSet {
    int start;
    int end;
};

class WaveSetPlayer {
private:
    int playPos;
    WaveSet ws;
    int repeat;
    int step;
    int playDir;
public:
    WaveSetPlayer(){
        playPos = -1;
        ws.start = -1;
        ws.end = -1;
        repeat = 0;
        step = 1;
    }

    /**
     * @brief playWS
     * @param ws WaveSet to play.
     * @param repeat Number of repetitons (1..*).
     * @param step Step size for the playback (i.e. -1 for reverse oder 2 for double speed).
     */
    void playWS(WaveSet ws, int repeat=1, int step=1){
        this->ws = ws;
        this->repeat = repeat-1;
        this->step = step;
        this->playDir = step/abs(step);
        playPos = ws.start;
    }

    /**
     * @brief Get the position of the next Sample of the waveset.
     * @return Sample position in the buffer.
     */
    int next() {
        if(playPos*playDir >= ws.end*playDir && repeat > 0){
            playPos = ws.start;
            repeat--;
        }

        if(playPos*playDir < ws.end*playDir) {
            int val = playPos;
            playPos+=step;
            return val;
        } else {
            printf("WaveSetPlayer::next() reached End of Waveset!\n");
            return -1;
        }
    }

    /**
     * @brief Number of samples that are left in current playing waveset.
     * @return Number of samples left.
     */
    int left() {
        return (ws.end-playPos-playDir)/step + (repeat*(ws.end-ws.start-playDir))/step;
    }
};

#endif // WAVESET_H
