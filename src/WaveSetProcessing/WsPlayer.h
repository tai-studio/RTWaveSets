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

class WsPlayer {
private:
    double playPos;
    WaveSetPlay ws; // TODO replace struct by simple startPos, endPos variables
    int repeat;
    float playRate;

public:
    WsPlayer();
    void playWS(WaveSetPlay ws, int repeat=1, float rate=1.0);
    double next();
    bool endOfPlay();
};

#endif // WAVESETITERATOR_H
