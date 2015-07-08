#include "SC_PlugIn.h"
#include "RTWaveSetAnalysis.h"
#include "RTWaveSetPlayer.h"

static InterfaceTable *ft;

// the entry point is called by the host when the plug-in is loaded
PluginLoad(RTWaveSetAnalysis)
{
    // InterfaceTable *inTable implicitly given as argument to the load function
    ft = inTable; // store pointer to InterfaceTable

    DefineSimpleUnit(RTWaveSetAnalysis);
    DefineSimpleUnit(RTWaveSetPlayer);
}
