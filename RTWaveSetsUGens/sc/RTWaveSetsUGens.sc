RTWaveSetAnalysis : UGen {
	*ar { arg audioBuf, wsBuf, in, active=1;
		^this.multiNew('audio', audioBuf, wsBuf, LeakDC.ar(in), active)
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

RTWaveSetPlayerContinuous : UGen {
	*ar { arg audioBuf, wsBuf, idx, rate=1, groupSize=1, repeat=1;
		^this.multiNew('audio', audioBuf, wsBuf, idx, rate, groupSize, repeat)
	}
}

RTWaveSetFeatureExtractor : UGen {
	*kr { arg audioBuf, wsBuf, feature, idx;
		var featureID = switch(feature,\dur , 0, \rms, 1);
		^this.multiNew('control', audioBuf, wsBuf, featureID, idx)
	}
}
