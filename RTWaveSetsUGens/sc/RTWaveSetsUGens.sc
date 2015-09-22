RTWaveSetAnalysis : UGen {
        *ar { arg audioBuf, xingsBuf, in, analysisOn=1;
                ^this.multiNew('audio', audioBuf, xingsBuf, in, analysisOn)
        }
}

RTWaveSetSelector : UGen {
        *ar { arg audioBuf, xingsBuf, desiredLen=(-1), desiredAmp=(-1);
                ^this.multiNew('audio', audioBuf, xingsBuf, desiredLen, desiredAmp)
        }
}

RTWaveSetPlayerTriggered : UGen {
    *ar { arg audioBuf, xingsBuf, repeats, numWS, xingIdx, trig, idxOffset, rate;
    ^this.multiNew('audio', audioBuf, xingsBuf, repeats, numWS, xingIdx, trig, idxOffset, rate)
    }
}

