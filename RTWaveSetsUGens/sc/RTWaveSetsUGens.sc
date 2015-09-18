RTWaveSetAnalysis : UGen {
        *ar { arg audioBuf, xingsBuf, in, analysisOn=1;
                ^this.multiNew('audio', audioBuf, xingsBuf, in, analysisOn)
        }
}

RTWaveSetSelector : UGen {
        *ar { arg audioBuf, xingsBuf, desiredLen;
                ^this.multiNew('audio', audioBuf, xingsBuf, desiredLen)
        }
}

RTWaveSetPlayerRepeat : UGen {
    *ar { arg audioBuf, xingsBuf, repeats, numWS, xingIdx, trig, idxOffset, rate;
    ^this.multiNew('audio', audioBuf, xingsBuf, repeats, numWS, xingIdx, trig, idxOffset, rate)
    }
}

RTWaveSetPlayerTriggered : UGen {
    *ar { arg audioBuf, xingsBuf, trigger, speed=1;
    ^this.multiNew('audio', audioBuf, xingsBuf, 4, trigger)
    }
}

RTWaveSetPlayer : UGen {

    *arTransformReverse { arg audioBuf, xingsBuf, speedMul=1;
        ^this.ar(audioBuf, xingsBuf, 1, speedMul)
    }

    *arTransformForward { arg audioBuf, xingsBuf, speedMul=1;
        ^this.ar(audioBuf, xingsBuf, 2, speedMul)
    }

    *arTransformRepeat { arg audioBuf, xingsBuf, repeats=1;
        ^this.ar(audioBuf, xingsBuf, 3, repeats)
    }

    *arRepeatTrigger { arg audioBuf, xingsBuf, trig;
        ^this.multiNew('audio', audioBuf, xingsBuf, 4, trig)
    }

    *ar { arg audioBuf, xingsBuf, transformation=0, param=0;
        ^this.multiNew('audio', audioBuf, xingsBuf, transformation, param)
    }
}
