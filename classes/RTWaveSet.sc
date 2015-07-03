
RTWaveSetAnalysis {
	*ar { arg audioBuf, xingsBuf, in;
		^this.multiNew('audio', audioBuf, xingsBuf, in)
	}
}


// naive
RTWaveSetPlayer {
	*ar { arg audioBuf, xingsBuf, idx;
		^this.multiNew('audio', audioBuf, xingsBuf, idx)
	}
}

// overly complex
RTWaveSetPlayerWithRepeats {
	*ar { arg
		audioBuf,
		xingsBuf,
		idx = 0,
		repeats = 1, // number of repeats of playback before looking at idx again
		context = 1; // how many WS before this should be included
		^this.multiNew('audio', audioBuf, xingsBuf, idx, repeats, context)
	}
}



// overly complex
RTWaveSetPlayerWithRepeats2 {
	*arDelay { // weird non-thinking method...
		var idx = idx -5;
		var trig = DelayN.kr(trig, 0.2, 0.2);

		^this.ar('audio', audioBuf, xingsBuf, idx, trig: trig)
	}

	*ar { arg
		audioBuf,
		xingsBuf,
		idx = 0,
		repeats = 1, // number of repeats of playback before looking at idx again
		context = 1; // how many WS before this should be included

		var trig = ...;
		^this.ar('audio', audioBuf, xingsBuf, idx, trig: trig)
	}


	*ar1 { arg
		audioBuf,
		xingsBuf,
		idx = 0,
		trig; // look for idx if trig > 0;

		^this.multiNew('audio', audioBuf, xingsBuf, idx, trig)
	}
}

// GrainIn

/*
totally explicit testing

(
q = ();

q.idxBus = Bus.audio(s);
q.aBuf = Buffer.alloc(s, 5 * s.sampleRate, 1);
q.xBuf = Buffer.alloc(s, 5 * s.sampleRate, 1);


{ // analysis
	var in = SoundIn.ar(0);
	var rtIdx;



	rtIdx = RTWaveSetAnalysis.ar(
		audioBuf: q.aBuf,
		xingsBuf: q.xBuf,
		in
	);

	Out.ar(q.idxBus.index, rtIdx);
}.play


{ // play back
	rtIdx = In.ar(q.idxBus.index, q.idxBus.numChannels);


	Out.ar(0, RTWaveSetPlayer.ar(
		audioBuf: q.aBuf,
		xingsBuf: q.xBuf,
		rtIdx
	));

}.play
)
*/

/*
(
{
	var in = SoundIn.ar(0);
	var rtIdx;
	var aBuf = LocalBuf(5 * s.sampleRate, 1);
	var xBuf = LocalBuf(5 * s.sampleRate, 1);

	// analysis
	rtIdx = RTWaveSetAnalysis.ar(
		audioBuf: aBuf,
		xingsBuf: xBuf,
		in
	);

	// playback
	Out.ar(0, RTWaveSetPlayer.ar(
		audioBuf: aBuf,
		xingsBuf: xBuf,
		rtIdx
	));


}.play
)
*/