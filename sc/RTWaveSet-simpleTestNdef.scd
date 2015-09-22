s.boot;

(

f = {
Ndef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });

//Ndef(\sound).play;

q = ();
q.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
q.xBuf = Buffer.alloc(s, 100000, 1);


// addSpec does not work?
/*Ndef(\wsRepeat).addSpec(\repetition, [1, 100]);
Ndef(\wsRepeat).addSpec(\numWS, [1, 100]);
Ndef(\wsRepeat).addSpec(\idxOffset, [0, 100]);*/


Ndef(\wsRepeat, {
		arg t_trig=0, repetition=10, numWS=1, idxOffset=0, analysisOn=1, rate=1, desiredLen=(-1), desiredAmp=(-1);
	var idx, idx2, out, trig;

	idx = RTWaveSetAnalysis.ar(q.aBuf, q.xBuf, Ndef(\sound).ar(1), analysisOn);

	idx2 = RTWaveSetSelector.ar(q.aBuf, q.xBuf, desiredLen, desiredAmp);
	//trig = T2A.ar(MouseButton.kr(-1,1,0,0.1));
	trig = T2A.ar(t_trig);

	RTWaveSetPlayerRepeat.ar(
		q.aBuf, q.xBuf, repetition, numWS, idx2-numWS+1, trig, idxOffset, rate
	);
});

Ndef(\wsRepeat).play;

};


//b = Buffer.read(s, "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav",0,-1,f);
b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav",0,-1,f);
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

~ would be great to have a trigger to turn analysis/recording of material on/off (DONE)

+ for longer periods of silence: just pause analysis and recording (?)


## RTWaveSetPlayerRepeat

~ Trigger: each time a trigger is received (A trigger occurs when at argument trig that signal changes from negative value to positive value), spawn a sound from the player, following the following parameters:

~	Wave idx (w0) (DONE)

~	number of included waves (wave idx is first, then the N following)
    (n=4): w0, w1, w2, w3 (DONE)

+	number of repetitions
		could be either interleaved (r=2): w0, w1, w2, w3, w0, w1, w2, w3
		or blocked (r=2): w0, w0, w1, w1, w2, w2, w3, w3
   (TODO: this feature will need bigger changes in the playback code)

~   playback rate: 1 == normal playback, 1.5 == faster, -0.275 slowly backwards
    (DONE, but so far implemented without interpolation, just repeat/skip samples)

---
+ = TODO
~ = DONE
---

Also great to have:

Intermediate units, which, based on (more or less) high-level parameters, calculate indices:

RTWaveSetDurAmp2Idx.ar(q.aBuf, q.xBuf, dur, amp)
-> amp == -1 : ignore amp
-> dur == -1 : ignore dur

returns index of the wave that is closest to given [dur, amp] combination

RTWaveSetPeakIdx.ar(q.aBuf, q.xBuf, windowSize)

*/