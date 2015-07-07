// without mul and add.
//RTWaveSet : UGen {
//    *ar { arg freq = 440.0, iphase = 0.0;
//        ^this.multiNew('audio', freq, iphase)
//    }
//    *kr { arg freq = 440.0, iphase = 0.0;
//        ^this.multiNew('control', freq, iphase)
//    }
//}


RTWaveSetAnalysis : UGen {
        *ar { arg audioBuf, xingsBuf, in;
                ^this.multiNew('audio', audioBuf, xingsBuf, in)
        }
}


RTWaveSetPlayer : UGen {
    *transformReverse { arg audioBuf, xingsBuf, idx, speedMul=1;
        ^this.ar(audioBuf, xingsBuf, idx, 1, speedMul)
    }

    *transformForward { arg audioBuf, xingsBuf, idx, speedMul=1;
        ^this.ar(audioBuf, xingsBuf, idx, 2, speedMul)
    }

    *transformRepeat { arg audioBuf, xingsBuf, idx, repeats=1;
        ^this.ar(audioBuf, xingsBuf, idx, 3, repeats)
    }

    *ar { arg audioBuf, xingsBuf, idx, transformation=0, param=0;
        ^this.multiNew('audio', audioBuf, xingsBuf, idx, transformation, param)
    }
}
