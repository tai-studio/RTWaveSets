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

    unit->audioBuf = FloatRingBuffer::getFromBuffer(ZIN0(0),unit);
    unit->xingsBuf = FloatRingBuffer::getFromBuffer(ZIN0(1),unit);

}



/**
 * @brief Get the latest Waveset that is in the given size range.
 * @param unit
 * @param minWavesetLength
 * @param maxWavesetLength
 * @return The WaveSet.
 */

WaveSetPlay RTWaveSetPlayer_latesWSinRange(RTWaveSetPlayer *unit, int minWavesetLength, int maxWavesetLength)
{
    WaveSetPlay ws;
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
 * @param numWS How many WaveSets starting vom xingIdx forward should be appended.
 * @return
 */

WaveSetPlay RTWaveSetPlayer_getWS(RTWaveSetPlayer *unit, int xingIdx, int numWS){
    WaveSetPlay ws;
    ws.start = -1;
    ws.end = -1;

    int startIdx = xingIdx;
    int endIdx = xingIdx + numWS;

    // check validity of parameters
    if(numWS<1) {
        printf("RTWaveSetPlayer Warning: numWS < 1");
        return ws;
    }

    float start = unit->xingsBuf->get(startIdx);
    float end = unit->xingsBuf->get(endIdx);

    if(isnan(end) || isnan(start) || end<1 || start<0)
    {
        printf("RTWaveSetPlayer Warning: no valid WaveSet found in xing Buffer!\n");
        return ws;
    }

    // cast to int
    ws.end = (int) end;
    ws.start = (int) start;

    return ws;
}

void RTWaveSetPlayer_Dtor( RTWaveSetPlayer *unit ) {

}
