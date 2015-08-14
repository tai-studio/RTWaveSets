#include "RTWaveSetPlayer.h"
// define RTWaveSetPlayer_DEBUG


/**
 * @brief RTWaveSetPlayer_Ctor Constructor for the RTWaveSetPlayer UGen.
 * @param unit
 */

void RTWaveSetPlayer_Ctor( RTWaveSetPlayer *unit ) {
    #ifdef RTWaveSetPlayer_DEBUG
    printf("RTWaveSetPlayer_Ctor()\n");
    #endif

    unit->audioBuf = SoundRingBuffer::getFromBuffer(ZIN0(0),unit);
    unit->xingsBuf = SoundRingBuffer::getFromBuffer(ZIN0(1),unit);

    // initialize the unit generator state variables.
    unit->wsp = WaveSetIterator();

}



/**
 * @brief Get the latest Waveset that is in the given size range.
 * @param unit
 * @param minWavesetLength
 * @param maxWavesetLength
 * @return The WaveSet.
 */

WaveSet RTWaveSetPlayer_latesWSinRange(RTWaveSetPlayer *unit, int minWavesetLength, int maxWavesetLength)
{
    WaveSet ws;
    ws.start = -1;
    ws.end = -1;


    if(unit->xingsBuf->getLastPos()>=1&& unit->audioBuf->getLastPos()>=maxWavesetLength)
    // wait for at least one zerocrossing and enouph input samples for a waveset mit max length
    {
        // zerocrossings "backward-index" of the waveset
        int endBack = 0;
        int startBack = endBack+1;

        // search for for a WaveSet with the right length, beginning at the end.
        int wsLen;
        do {
            ws.end=unit->xingsBuf->getLast(endBack);
            ws.start=unit->xingsBuf->getLast(startBack);
            wsLen = ws.end - ws.start;

            // if the Waveset it too long take the next one
            if(wsLen>maxWavesetLength)
            {
                endBack++;
                startBack = endBack+1;
                #ifdef RTWaveSetPlayer_DEBUG
                printf("RTWaveSetAnalysis_latesWSinRange() Warning: skipping too long WaveSet!");
                #endif
            }

            // if the WS is too short extend to the next zerocrossing.
            if(wsLen<minWavesetLength)
            {
                startBack++;
            }

            if(startBack > unit->xingsBuf->getLastPos()) break; // give up when reached beginning

        } while(wsLen < minWavesetLength || wsLen > maxWavesetLength);
    }

    #ifdef RTWaveSetPlayer_DEBUG
    printf("RTWaveSetPlayer_getWS() len:%i\n",ws.end-ws.start);
    #endif
    return ws;
}

/**
 * @brief Get a WaveSet.
 * @param unit
 * @param xingIdx Index of the Xing. -1 for latest xing.
 * @param numWS How many WaveSets starting vom xingIdx backwards should be appended.
 * @return
 */

WaveSet RTWaveSetPlayer_getWS(RTWaveSetPlayer *unit, int xingIdx, int numWS){
    WaveSet ws;
    ws.start = -1;
    ws.end = -1;

    if(numWS<1) numWS = 1;

    if(xingIdx < numWS-1) xingIdx = unit->xingsBuf->getLastPos();
    if(xingIdx > unit->xingsBuf->getLastPos()) xingIdx = unit->xingsBuf->getLastPos();

    if(unit->xingsBuf->getLastPos() >= numWS)
    {
        ws.end = unit->xingsBuf->get(xingIdx);
        ws.start = unit->xingsBuf->get(xingIdx - numWS);
    }

    return ws;
}

void RTWaveSetPlayer_Dtor( RTWaveSetPlayer *unit ) {

}
