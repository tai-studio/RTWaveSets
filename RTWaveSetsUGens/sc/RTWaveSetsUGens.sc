RTWaveSetAnalysis : UGen {
        *ar { arg audioBuf, xingsBuf, in;
                ^this.multiNew('audio', audioBuf, xingsBuf, in)
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

    *ar { arg audioBuf, xingsBuf, transformation=0, param=0;
        ^this.multiNew('audio', audioBuf, xingsBuf, transformation, param)
    }
}
