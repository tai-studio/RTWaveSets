#include "SC_PlugIn.h"
#include "RTWavesetAnalysis.h"
#include "RTWavesetSynthTriggered.h"
#include "RTWavesetSelector.h"
#include "RTWavesetFeatureExtractor.h"
#include "RTWavesetSynthContinuous.h"
#include "ScObject.h"

static InterfaceTable *ft;

// the entry point is called by the host when the plug-in is loaded
PluginLoad(RTWavesetAnalysis)
{
    // InterfaceTable *inTable implicitly given as argument to the load function
    ft = inTable; // store pointer to InterfaceTable
    ScObject::setScInterface(ft);

    DefineDtorUnit(RTWavesetAnalysis);
    DefineDtorUnit(RTWavesetSynthTriggered);
    DefineDtorUnit(RTWavesetSynthContinuous);
    DefineDtorUnit(RTWavesetSelector);
    DefineDtorUnit(RTWavesetFeatureExtractor);
}
