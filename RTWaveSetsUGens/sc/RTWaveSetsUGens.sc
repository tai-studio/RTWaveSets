RTWaveSetAnalysis : UGen {
        *ar { arg audioBuf, wsBuf, in, active=1;
                ^this.multiNew('audio', audioBuf, wsBuf, in, active)
        }
}

RTWaveSetSelector : UGen {
        *ar { arg audioBuf, wsBuf, desiredDur=(-1), desiredAmp=(-1);
                ^this.multiNew('audio', audioBuf, wsBuf, desiredDur, desiredAmp)
        }
}

RTWaveSetPlayerTriggered : UGen {
    *ar { arg audioBuf, wsBuf, trig, idx, rate=1, groupSize=1, repeat=1;
    ^this.multiNew('audio', audioBuf, wsBuf, trig, idx, rate, groupSize, repeat)
    }
}
