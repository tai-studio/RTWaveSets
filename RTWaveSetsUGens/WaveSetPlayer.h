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
    WaveSetPlayer();
    void playWS(WaveSet ws, int repeat=1, int step=1);
    int next();
    int left();
};

#endif // WAVESET_H
