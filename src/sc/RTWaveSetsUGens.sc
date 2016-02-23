RTWaveSetData {
	var <audioBufSize, <wsBufSize;
	var <server;
	var <audioBuf, <wsBuf;

	*new{ arg audioBufSize=1000000, wsBufSize=10000, server(Server.default);
		^super.newCopyArgs(audioBufSize, wsBufSize, server).init
	}

	init {
		audioBuf = Buffer.alloc(server, audioBufSize);
		wsBuf = Buffer.alloc(server, wsBufSize);
    }
}

RTWaveSetAnalysis : MultiOutUGen {
	*ar { arg wsData, in, active=1, minWSLen=0.0005;
		^this.multiNew('audio', wsData.audioBuf, wsData.wsBuf, in, active, minWSLen)
	}

	init { arg ... theInputs;
		inputs = theInputs;
		channels = [
			OutputProxy(rate, this, 0),
			OutputProxy(rate, this, 1)
		];
		^channels
	}
}


RTWaveSetSelector : UGen {
	*ar { arg wsData, dur=(-1), rms=(-1), lookBackLimit=(-1);
		^this.multiNew('audio', wsData.audioBuf, wsData.wsBuf, dur, rms, lookBackLimit)
	}
}

RTWaveSetPlayerTriggered : UGen {
	*ar { arg wsData, trig, idx, rate=1, groupSize=1, repeat=1;
		^this.multiNew('audio', wsData.audioBuf, wsData.wsBuf, trig, idx, rate, groupSize, repeat)
	}
}

RTWaveSetPlayerContinuous : UGen {
	*ar { arg wsData, idx, rate=1, groupSize=1, repeat=1;
		^this.multiNew('audio', wsData.audioBuf, wsData.wsBuf, idx, rate, groupSize, repeat)
	}
}

RTWaveSetFeatureExtractor : UGen {
	*kr { arg wsData, feature, idx;
		var featureID = switch(feature,\dur , 0, \rms, 1);
		^this.multiNew('control', wsData.audioBuf, wsData.wsBuf, featureID, idx)
	}
}