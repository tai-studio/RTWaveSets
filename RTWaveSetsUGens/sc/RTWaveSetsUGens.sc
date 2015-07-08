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
    *transformReverse { arg audioBuf, xingsBuf, speedMul=1;
        ^this.ar(audioBuf, xingsBuf, 1, speedMul)
    }

    *transformForward { arg audioBuf, xingsBuf, speedMul=1;
        ^this.ar(audioBuf, xingsBuf, 2, speedMul)
    }

    *transformRepeat { arg audioBuf, xingsBuf, repeats=1;
        ^this.ar(audioBuf, xingsBuf, 3, repeats)
    }

    *ar { arg audioBuf, xingsBuf, transformation=0, param=0;
        ^this.multiNew('audio', audioBuf, xingsBuf, transformation, param)
    }
}
