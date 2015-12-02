RTWaveSetAnalysis : UGen {
        *ar { arg audioBuf, wsBuf, in, active=1;
                ^this.multiNew('audio', audioBuf, wsBuf, in, active)
        }
}

RTWaveSetSelector : UGen {
        *ar { arg audioBuf, wsBuf, dur=(-1), rms=(-1);
                ^this.multiNew('audio', audioBuf, wsBuf, dur, rms)
        }
}

RTWaveSetPlayerTriggered : UGen {
    *ar { arg audioBuf, wsBuf, trig, idx, rate=1, groupSize=1, repeat=1;
    ^this.multiNew('audio', audioBuf, wsBuf, trig, idx, rate, groupSize, repeat)
    }
}
