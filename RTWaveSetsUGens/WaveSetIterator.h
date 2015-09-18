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
    double playPos;
    WaveSet ws;
    int repeat;
    float playRate;

public:
    WaveSetIterator();
    void playWS(WaveSet ws, int repeat=1, float rate=1.0);
    int next();
    int left();
    int getPlayRate(){ return playRate; }
};

#endif // WAVESET_H
