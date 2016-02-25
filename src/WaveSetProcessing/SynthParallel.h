#ifndef SYNTHTRIGGERED_H
#define SYNTHTRIGGERED_H

#include "Synth.h"


/**
 * @brief Implements event-based waveset synthesis with a limited number of parallel wavesets.
 */

class SynthParallel : public Synth
{

public:
    SynthParallel(WsStorage* wsData);
    void startNewPlayback(int idxIn,int groupSize,float rate,int repeat);
    float getNextOutput();

    /** max number of possible parallel playbacks */
    static const int numPlayers = 512;

private:

    /** Players for parallel WS Playbacks */
    WsPlayer wsPlayers[numPlayers];

    /** idx of last playing iterator in the  wsPlayers array */
    int lastActiveIteratorIdx;

};

#endif // SYNTHTRIGGERED_H
