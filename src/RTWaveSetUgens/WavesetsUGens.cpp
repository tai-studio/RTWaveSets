#include "SC_PlugIn.h"
#include "WavesetAnalysis.h"
#include "WavesetSynthTriggered.h"
#include "WavesetSelector.h"
#include "WavesetGetFeature.h"
#include "WavesetSynthContinuous.h"
#include "ScObject.h"

static InterfaceTable *ft;

// the entry point is called by the host when the plug-in is loaded
PluginLoad(WavesetAnalysis)
{
    // InterfaceTable *inTable implicitly given as argument to the load function
    ft = inTable; // store pointer to InterfaceTable
    ScObject::setScInterface(ft);

    DefineDtorUnit(WavesetAnalysis);
    DefineDtorUnit(WavesetSynthTriggered);
    DefineDtorUnit(WavesetSynthContinuous);
    DefineDtorUnit(WavesetSelector);
    DefineDtorUnit(WavesetGetFeature);
}
