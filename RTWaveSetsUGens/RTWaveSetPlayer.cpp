#include "RTWaveSetPlayer.h"



/**
 * @brief RTWaveSetPlayer_Ctor Constructor for the RTWaveSetPlayer UGen.
 * @param unit
 */

void RTWaveSetPlayer_Ctor( RTWaveSetPlayer *unit ) {
    printf("RTWaveSetPlayer_Ctor()\n");

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
                printf("RTWaveSetAnalysis_latesWSinRange() Warning: skipping too long WaveSet!");
            }

            // if the WS is too short extend to the next zerocrossing.
            if(wsLen<minWavesetLength)
            {
                startBack++;
            }

            if(startBack > unit->xingsBuf->getLastPos()) break; // give up when reached beginning

        } while(wsLen < minWavesetLength || wsLen > maxWavesetLength);
    }

    printf("RTWaveSetPlayer_getWS() len:%i\n",ws.end-ws.start);
    return ws;
}

/**
 * @brief Get the latest WaveSet.
 * @param unit
 * @param idxBack delay of N wavesets.
 * @param numWS How many WaveSets starting vom idxBack backwards should be appended.
 * @return
 */

WaveSet RTWaveSetPlayer_getWS(RTWaveSetPlayer *unit, int idxBack, int numWS){
    WaveSet ws;
    ws.start = -1;
    ws.end = -1;

    if(numWS<1) numWS = 1;

    if(unit->xingsBuf->getLastPos()>=(numWS+idxBack))
    {
        ws.end = unit->xingsBuf->getLast(idxBack);
        ws.start = unit->xingsBuf->getLast(idxBack + numWS);
    }

    return ws;
}

void RTWaveSetPlayer_Dtor( RTWaveSetPlayer *unit ) {

}
