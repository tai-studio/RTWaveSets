// without mul and add.
//RTWaveSet : UGen {
//    *ar { arg freq = 440.0, iphase = 0.0;
//        ^this.multiNew('audio', freq, iphase)
//    }
//    *kr { arg freq = 440.0, iphase = 0.0;
//        ^this.multiNew('control', freq, iphase)
//    }
//}


/*RTWaveSetAnalysis {
        *ar { arg audioBuf, xingsBuf, in;
                ^this.multiNew('audio', audioBuf, xingsBuf, in)
        }
}

RTWaveSetPlayer {
        *ar { arg audioBuf, xingsBuf, idx;
                ^this.multiNew('audio', audioBuf, xingsBuf, idx)
        }
}*/

RTWaveSetAnalysis : UGen {
    *transformReverse { |audioBuffer, zeroCrossingBuffer, in, speedMul=1|
        ^this.ar(audioBuffer, zeroCrossingBuffer, in, 1, speedMul)
    }

    *transformForward { |audioBuffer, zeroCrossingBuffer, in, speedMul=1|
        ^this.ar(audioBuffer, zeroCrossingBuffer, in, 2, speedMul)
    }

    *transformRepeat { |audioBuffer, zeroCrossingBuffer, in, repeats=1|
        ^this.ar(audioBuffer, zeroCrossingBuffer, in, 3, repeats)
    }

    *ar { |audioBuffer, zeroCrossingBuffer, in, transformation=0, param=0|
        ^this.multiNew('audio', audioBuffer, zeroCrossingBuffer, in, transformation, param)
    }
}
