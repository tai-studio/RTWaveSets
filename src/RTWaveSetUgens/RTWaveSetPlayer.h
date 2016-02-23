#ifndef RTWAVESETPLAYER_H
#define RTWAVESETPLAYER_H

#include "RTWaveSetBase.h"
#include "WaveSetProcessing/WaveSetIterator.h"

static const int minWavesetLength = (int) (3.0 * 44.100); // 3 ms
static const int maxWavesetLength = (int) (500.0 * 44.100); // 500 ms

struct RTWaveSetPlayer : public RTWaveSetBase  {

};

void RTWaveSetPlayer_Ctor(RTWaveSetPlayer *unit);
//void RTWaveSetPlayer_next(RTWaveSetPlayer *unit, int inNumSamples); // now using calc functions in inherited players
void RTWaveSetPlayer_Dtor(RTWaveSetPlayer *unit);
void RTWaveSetPlayer_playGroup(RTWaveSetPlayer *unit);

WaveSetPlay RTWaveSetPlayer_getWS(RTWaveSetPlayer *unit, int wsIdx, int groupSize);
void RTWaveSetPlayer_playGroup(WaveSetIterator* wsi,RTWaveSetPlayer *unit,int repeat, int groupSize, int xingIdx, float rate);
float RTWaveSetPlayer_getSample(RTWaveSetPlayer *unit, double idx);

#endif // RTWAVESETPLAYER_H