#ifndef SYNTHTRIGGERED_H
#define SYNTHTRIGGERED_H

#include "Synth.h"

#define SynthTriggered_NumIterators 512

class SynthTriggered : public Synth
{
private:
    /** Iterators for parallel WS Playbacks */
    WsPlayer wsIterators[SynthTriggered_NumIterators];

    /** index of last playing iterator in array */
    int lastActiveIteratorIdx;

public:
    SynthTriggered(WsStorage* wsData);
    void startNewPlayback(int idxIn,int groupSize,float rate,int repeat);
    float getNextOutput();



};

#endif // SYNTHTRIGGERED_H
