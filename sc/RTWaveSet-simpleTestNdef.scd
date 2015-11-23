s.boot;


b = Buffer.read(s, "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav",0,-1,f);

/*
b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav",0,-1,f);
*/

Ndef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });
Ndef(\sound).play;

NdefMixer(s)

q = ();
q.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
q.xBuf = Buffer.alloc(s, 100000, 1);

(
// addSpec >> install JITLibExtensions quark
Ndef(\wsRepeat).addSpec(\repetitions, [1, 100, \lin, 1]);
Ndef(\wsRepeat).addSpec(\numWS, [1, 100]);
Ndef(\wsRepeat).addSpec(\idxOffset, [0, 100]);
Ndef(\wsRepeat).addSpec(\trigRate, [1, 100]);
Ndef(\wsRepeat).addSpec(\rt, [0, 1, \lin, 1 ]);
Ndef(\wsRepeat).addSpec(\wsDur, [0, 1, \lin]);
Ndef(\wsRepeat).addSpec(\setDur, [0, 1, \lin, 1]);


Ndef(\wsRepeat, {
	var trig, repetitions, numWS, idxOffset, analyse, rate, wsDur, wsAmp, rt;
	var idx, rtIdx, selectorIdx, out;

	// trig        = T2A.ar(\trig.tr(0)); // audiorate trigger
	trig        = Impulse.ar(\trigRate.kr(10));
	repetitions = \repetitions.kr(10);
	numWS       = \numWS.kr(1);
	idxOffset   = \idxOffset.kr(0);
	rate        = \rate.kr(1);
	wsDur       = \wsDur.kr(-1);
	wsAmp       = \wsAmp.kr(-1);
	analyse     = \analyse.kr(1);
	rt          = \rt.kr(0); // if 1, rtIdx is used, otherwise analysis.

	wsDur       = Select.kr(\setDur.kr(0), [-1, wsDur]);


	// analysis returns idx of last recorded WS
	rtIdx = RTWaveSetAnalysis.ar(q.aBuf, q.xBuf,
		Ndef(\sound).ar(1),
		analyse
	);
	// select WS index based on desired amplitude / duration
	selectorIdx = RTWaveSetSelector.ar(q.aBuf, q.xBuf, wsDur, wsAmp);

	idx = Select.kr(rt, [selectorIdx, rtIdx]);


	RTWaveSetPlayerTriggered.ar(q.aBuf, q.xBuf,
		repetitions, numWS, idx, trig, idxOffset, rate
	)!2;
});
)
Ndef(\wsRepeat).play;



)



Ndef(\wsRepeat).set(\t_trig, 1)
Ndef(\wsRepeat).set(\repetition, 100)
Ndef(\wsRepeat).set(\numWS,5)
Ndef(\wsRepeat).set(\analysisOn, -1)
Ndef(\wsRepeat).set(\analysisOn, 1)
Ndef(\wsRepeat).set(\rate, 1)

Ndef(\wsRepeat).set(\desiredLen, -1) // in ms
Ndef(\wsRepeat).set(\desiredLen, 0) // in ms
Ndef(\wsRepeat).set(\desiredLen, 4) // in ms
Ndef(\wsRepeat).set(\desiredLen, 10) // in ms

Ndef(\wsRepeat).set(\desiredAmp, -1)
Ndef(\wsRepeat).set(\desiredAmp, 0)
Ndef(\wsRepeat).set(\desiredAmp, 0.2)
Ndef(\wsRepeat).set(\desiredAmp, 1)

/*
Notes:

## RTWaveSetAnalysis

+ would be great to have a trigger to turn analysis/recording of material on/off
-> DONE: Argument analysisOn: Enable (>0) or pause (<=0) the analysis.

+ for longer periods of silence: just pause analysis and recording (?)
-> TODO

## RTWaveSetPlayerRepeat -> now RTWaveSetPlayerTriggered

+ Trigger: each time a trigger is received (A trigger occurs when at argument trig that signal changes from negative value to positive value), spawn a sound from the player, following the following parameters:
-> DONE: Argument trig: Trigger to start the playback of the defined wavesets. There are up to 30 parallel playbacks possible.

+	Wave idx (w0) (DONE)

+	number of included waves (wave idx is first, then the N following)
(n=4): w0, w1, w2, w3 (DONE)
-> DONE: Argument numWS: Number of wavesets starting from the given index forward that well be combined to a group and played.
It might be discussed if it's more reasonable to go forward or backward, or both 50/50? One point is that it's not possible to go forward if we are at the latest waveset.

+	number of repetitions
could be either interleaved (r=2): w0, w1, w2, w3, w0, w1, w2, w3
or blocked (r=2): w0, w0, w1, w1, w2, w2, w3, w3
-> so far only interleaved repeat
TODO: blocked repeat will need bigger changes in the playback code.

+   playback rate: 1 == normal playback, 1.5 == faster, -0.275 slowly backwards
-> DONE: but so far implemented without interpolation, just repeat/skip samples.
TODO: interpolation

Also great to have:
Intermediate units, which, based on (more or less) high-level parameters, calculate indices:
RTWaveSetDurAmp2Idx.ar(q.aBuf, q.xBuf, dur, amp)
-> amp == -1 : ignore amp
-> dur == -1 : ignore dur
returns index of the wave that is closest to given [dur, amp] combination

-> DONE: UGen RTWaveSetSelector to select WaveSets by duration and amplitude.
Is amp for Amplitude? I decided to use Root Mean Square.
Selection by duration works great but selection by amp worked not as expected for me.
Weight for a comibnation of amp and dur criteria are hard coded so far.

RTWaveSetPeakIdx.ar(q.aBuf, q.xBuf, windowSize)

*/