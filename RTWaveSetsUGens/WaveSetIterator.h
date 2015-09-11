#ifndef WAVESET_H
#define WAVESET_H

#include "SC_PlugIn.h"

struct WaveSet {
    int start;
    int end;
};

/**
 * @brief The WaveSetPlayer class
 */

class WaveSetIterator {
private:
    int playPos;
    WaveSet ws;
    int repeat;
    int step;
    int playDir;

public:
    WaveSetIterator();
    void playWS(WaveSet ws, int repeat=1, int step=1);
    int next();
    int left();
    int getStep(){ return step; }
};

#endif // WAVESET_H
