#ifndef RTWAVESETPLAYER_H
#define RTWAVESETPLAYER_H

#include "RTWaveSetBase.h"
#include "WaveSetPlayer.h"

static const int minWavesetLength = (int) (3.0 * 44.100); // 3 ms
static const int maxWavesetLength = (int) (500.0 * 44.100); // 500 ms

enum Transformation {
    TRANS_NO=0,
    TRANS_REVERSE=1,
    TRANS_FASTER=2,
    TRANS_REPEAT=3
};

struct RTWaveSetPlayer : public RTWaveSetBase  {

    /** Variables for Waveset play */
    WaveSetPlayer wsp;

    /** type of transformation */
    Transformation transformation;
};

void RTWaveSetPlayer_Ctor(RTWaveSetPlayer *unit);
void RTWaveSetPlayer_next(RTWaveSetPlayer *unit, int inNumSamples);
void RTWaveSetPlayer_Dtor(RTWaveSetPlayer *unit);
void RTWaveSetPlayer_playNextWS(RTWaveSetPlayer *unit);

WaveSet RTWaveSetPlayer_latesWSinRange(RTWaveSetPlayer *unit, int minWavesetLength, int maxWavesetLength);



#endif // RTWAVESETPLAYER_H
