#ifndef WAVESETITERATOR_H
#define WAVESETITERATOR_H

#include "SC_PlugIn.h"
#include "AudioPiece.h"

/**
 * @brief The WsPlayer class
 */

class WsPlayer : public WsObject {
private:
    double playPos;
    AudioPiece ws;
    int repeat;
    float playRate;

public:
    WsPlayer();
    void playWS(AudioPiece ws, int repeat=1, float rate=1.0);
    double nextPos();
    float nextSample();
    bool endOfPlay();
};

#endif // WAVESETITERATOR_H
