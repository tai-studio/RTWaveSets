#ifndef WAVESETITERATOR_H
#define WAVESETITERATOR_H

#include "SC_PlugIn.h"

struct WaveSetPlay {
    int start;
    int end;
};

/**
 * @brief The WaveSetPlayer class
 */

class WaveSetIterator {
private:
    double playPos;
    WaveSetPlay ws;
    int repeat;
    float playRate;

public:
    WaveSetIterator();
    void playWS(WaveSetPlay ws, int repeat=1, float rate=1.0);
    int next();
    int left();
    int getPlayRate(){ return playRate; }
};

#endif // WAVESETITERATOR_H
