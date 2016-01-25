#ifndef WAVESETITERATOR_H
#define WAVESETITERATOR_H

#include "SC_PlugIn.h"

struct WaveSetPlay {
    int start;
    int end;
};

/**
 * @brief Iterator used to get the samples of wavesets for playback.
 * Impelemented features:
 *  Repeats of a WaveSet
 *  playback rate: 1 == normal playback, 1.5 == faster, -0.275 slowly backwards
 *                (so far implemented without interpolation, just repeat/skip samples)
 */

class WaveSetIterator {
private:
    double playPos;
    WaveSetPlay ws; // TODO replace struct by simple startPos, endPos variables
    int repeat;
    float playRate;

public:
    WaveSetIterator();
    void playWS(WaveSetPlay ws, int repeat=1, float rate=1.0);
    float next();
    bool endOfPlay();
    int getPlayRate(){ return playRate; }
};

#endif // WAVESETITERATOR_H
