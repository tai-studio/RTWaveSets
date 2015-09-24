RTWaveSetAnalysis : UGen {
        *ar { arg audioBuf, wsBuf, in, analysisOn=1;
                ^this.multiNew('audio', audioBuf, wsBuf, in, analysisOn)
        }
}

RTWaveSetSelector : UGen {
        *ar { arg audioBuf, wsBuf, desiredDur=(-1), desiredAmp=(-1);
                ^this.multiNew('audio', audioBuf, wsBuf, desiredDur, desiredAmp)
        }
}

RTWaveSetPlayerTriggered : UGen {
    *ar { arg audioBuf, wsBuf, repeats, numWS, xingIdx, trig, idxOffset, rate;
    ^this.multiNew('audio', audioBuf, wsBuf, repeats, numWS, xingIdx, trig, idxOffset, rate)
    }
}
