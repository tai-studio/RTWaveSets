#include "SC_PlugIn.h"
#include "waveset.h"
#include "soundringbuffer.h"
#include "soundringbuffer.cpp"

static InterfaceTable *ft;

static const int minWavesetLength = (int) (3.0 * 44.100); // 3 ms
static const int maxWavesetLength = (int) (500.0 * 44.100); // 500 ms

enum Transformation {
    TRANS_NO=0,
    TRANS_REVERSE=1,
    TRANS_FASTER=2,
    TRANS_REPEAT=3
};

struct RTWaveSetBase : public Unit {
    /** Ringbuffer for Input Audio */
    SoundRingBuffer inBuffer;

    /** Ringbuffer for found ZeroCrossings */
    SoundRingBuffer zeroBuffer;
};

// declare struct to hold unit generator state
struct RTWaveSetAnalysis : public RTWaveSetBase  {

};

struct RTWaveSetPlayer : public RTWaveSetBase  {

    /** Variables for Waveset play */
    WaveSetPlayer wsp;

    /** type of transformation */
    Transformation transformation;
};

// function declarations
void RTWaveSetBase_Ctor(RTWaveSetBase *unit);

void RTWaveSetAnalysis_Ctor(RTWaveSetAnalysis *unit);
void RTWaveSetAnalysis_next(RTWaveSetAnalysis *unit, int inNumSamples);
void RTWaveSetAnalysis_Dtor(RTWaveSetAnalysis *unit);

void RTWaveSetPlayer_Ctor(RTWaveSetPlayer *unit);
void RTWaveSetPlayer_next(RTWaveSetPlayer *unit, int inNumSamples);
void RTWaveSetPlayer_Dtor(RTWaveSetPlayer *unit);
void RTWaveSetPlayer_playNextWS(RTWaveSetPlayer *unit);

WaveSet RTWaveSetPlayer_latesWSinRange(RTWaveSetPlayer *unit, int minWavesetLength, int maxWavesetLength);

/**
 * @brief RTWaveSetBase_Ctor Constructor of the RTWaveSet base UGEN.
 * @param unit
 */

void RTWaveSetBase_Ctor(RTWaveSetBase *unit) {
    Print("RTWaveSetBase_Ctor()\n");

    // receive Audio Buffer arg
    unit->inBuffer = SoundRingBuffer(ZIN0(0),unit);
    printf("RTWaveSetAnalysis_Ctor: inBuffer (bufnum=%i,len=%i)\n",(int)(ZIN0(0)),unit->inBuffer.getLen());

    // receive Zero Crossing Buffer
    unit->zeroBuffer = SoundRingBuffer(ZIN0(1),unit);
    printf("RTWaveSetAnalysis_Ctor: zeroBuffer (bufnum=%i,len=%i)\n",(int)(ZIN0(1)),unit->zeroBuffer.getLen());
}

/**
 * @brief RTWaveSetAnalysis_Ctor Constructor for the RTWaveSetAnalysis UGen.
 * @param unit
 */

void RTWaveSetAnalysis_Ctor( RTWaveSetAnalysis *unit ) {
    Print("RTWaveSetAnalysis_Ctor()\n");

    // 1. set the calculation function.
    SETCALC(RTWaveSetAnalysis_next);

    RTWaveSetBase_Ctor(unit);

    // 3. calculate one sample of output.
    RTWaveSetAnalysis_next(unit, 1);
}

/**
 * @brief RTWaveSetPlayer_Ctor Constructor for the RTWaveSetPlayer UGen.
 * @param unit
 */

void RTWaveSetPlayer_Ctor( RTWaveSetPlayer *unit ) {
    Print("RTWaveSetPlayer_Ctor()\n");

    RTWaveSetBase_Ctor(unit);
    
    // set the calculation function.
    SETCALC(RTWaveSetPlayer_next);

    // initialize the unit generator state variables.
    unit->wsp = WaveSetPlayer();

    // receive Transformation type
    unit->transformation = (Transformation) IN0(3);
    printf("RTWaveSetAnalysis_Ctor: transformation=%i\n",unit->transformation);

    // 3. calculate one sample of output.
    RTWaveSetPlayer_next(unit, 1);
}

/**
 * @brief RTWaveSetAnalysis_next Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetAnalysis_next( RTWaveSetAnalysis *unit, int inNumSamples ) {
    
    float *in = IN(2);
    float *out = OUT(0);
    
    // Input Processing
    for ( int i=0; i<inNumSamples; ++i) {
        //out[i] = 0.0;

        float prev = unit->inBuffer.getLast();

        // save to Buffer
        unit->inBuffer.put(in[i]);

        // look for a -/+ zero crossing
        if(prev <= 0.0 && in[i] > 0.0) {
            // add zero crossing position to zeroBuffer
            unit->zeroBuffer.put(unit->inBuffer.getLastPos());
            //if(unit->zcPos >= 1) {out[i]=0.5;} // trigger that there is a new WaveSet
        }

        out[i] = unit->zeroBuffer.getLastPos();

    }

}


/**
 * @brief RTWaveSetAnalysis_next Process the next block of audio samples.
 * @param unit
 * @param inNumSamples
 */

void RTWaveSetPlayer_next( RTWaveSetPlayer *unit, int inNumSamples ) {

    float *in = IN(2);
    float *out = OUT(0);



    // Output Processing
    for ( int i=0; i<inNumSamples; ++i) {

        unit->zeroBuffer.setLastPos((int) in[i]);
        unit->inBuffer.setLastPos((int) unit->zeroBuffer.getLast()); // TODO transfer current buffer position directly

        // Samples left in WaveSetPlayer?
        if(unit->wsp.left()<1 && unit->zeroBuffer.getLastPos()>=1) {
            RTWaveSetPlayer_playNextWS(unit);
        }

        // play WaveSet
        if(unit->wsp.left()>0) {
            out[i] = unit->inBuffer.get(unit->wsp.next());
        }
        else{
            out[i] = 0.0;
        }

    }

}

/**
 * @brief RTWaveSetAnalysis_playNext Find the next WaveSet to play.
 * @param unit
 */
void RTWaveSetPlayer_playNextWS(RTWaveSetPlayer *unit){

    WaveSet ws;

    float param = IN0(4);

    switch(unit->transformation)
    {
    case TRANS_REVERSE: {
        int step = 1;
        ws = RTWaveSetPlayer_latesWSinRange(unit,minWavesetLength,maxWavesetLength);
        int h = ws.end;
        ws.end = ws.start;
        ws.start = h;
        if(param>1 && param<minWavesetLength) {
            step = (int) param;
        }
        unit->wsp.playWS(ws,1,-step);
        } break;
    case TRANS_FASTER: {
        int step = 1;
        if(param>1 && param<minWavesetLength) {
            step = (int) param;
        }
        unit->wsp.playWS(RTWaveSetPlayer_latesWSinRange(unit,minWavesetLength,maxWavesetLength),1,step);
        } break;
    case TRANS_REPEAT: {
        int repeat = 1;
        if(param>1 && param <= unit->inBuffer.getLen()/maxWavesetLength) {
            repeat = (int) param;
        }
        unit->wsp.playWS(RTWaveSetPlayer_latesWSinRange(unit,minWavesetLength,maxWavesetLength),repeat,1);
        } break;
    case TRANS_NO:
    default:
        ws = {unit->inBuffer.getLastPos()-512,unit->inBuffer.getLastPos()};
        unit->wsp.playWS(ws,1,1);
    }
}

/**
 * @brief RTWaveSetAnalysis_findLatesWSinRange Find the latest Waveset that is in the given size range.
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


    if(unit->zeroBuffer.getLastPos()>=1&& unit->inBuffer.getLastPos()>=maxWavesetLength)
    // wait for at least one zerocrossing and enouph input samples for a waveset mit max length
    {
        // zerocrossings "backward-index" of the waveset
        int endBack = 0;
        int startBack = endBack+1;

        // search for for a WaveSet with the right length, beginning at the end.
        int wsLen;
        do {
            ws.end=unit->zeroBuffer.getLast(endBack);
            ws.start=unit->zeroBuffer.getLast(startBack);
            wsLen = ws.end - ws.start;

            // if the Waveset it soo long take the next one
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

            if(startBack > unit->zeroBuffer.getLastPos()) break; // give up when reached beginning

        } while(wsLen < minWavesetLength || wsLen > maxWavesetLength);
    }

    return ws;
}

void RTWaveSetAnalysis_Dtor( RTWaveSetAnalysis *unit ) {

}

void RTWaveSetPlayer_Dtor( RTWaveSetPlayer *unit ) {

}

// the entry point is called by the host when the plug-in is loaded
PluginLoad(RTWaveSetAnalysis)
{
    // InterfaceTable *inTable implicitly given as argument to the load function
    ft = inTable; // store pointer to InterfaceTable

    DefineSimpleUnit(RTWaveSetAnalysis);
    DefineSimpleUnit(RTWaveSetPlayer);
}
