s.boot;

(

f = {
Ndef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });

//Ndef(\sound).play;

q = ();
q.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
q.xBuf = Buffer.alloc(s, 100000, 1);


/*Ndef(\wsRepeat).addSpec(\repetition, [1, 100]);
Ndef(\wsRepeat).addSpec(\numWS, [1, 100]);
Ndef(\wsRepeat).addSpec(\xingIdx, [-1, 1]);
Ndef(\wsRepeat).addSpec(\hold, [0, 1]);
Ndef(\wsRepeat).addSpec(\idxOffset, [0, 100]);*/


Ndef(\wsRepeat, {
	arg t_trig=0, repetition=10, numWS=20, xingIdx=(-1), idxOffset=0, analysisOn=1;
	var idx, out, trig;

	idx = RTWaveSetAnalysis.ar(q.aBuf, q.xBuf, Ndef(\sound).ar(1), analysisOn);
	//trig = T2A.ar(MouseButton.kr(-1,1,0,0.1));
	trig = T2A.ar(t_trig);

	RTWaveSetPlayerRepeat.ar(
		q.aBuf, q.xBuf, repetition, numWS, idx, trig, idxOffset
	);
});

Ndef(\wsRepeat).play;

};


//b = Buffer.read(s, "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav",0,-1,f);
b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav",0,-1,f);
)

Ndef(\wsRepeat).set(\repetition, 50)
Ndef(\wsRepeat).set(\t_trig, 1)
Ndef(\wsRepeat).set(\numWS, 10)
Ndef(\wsRepeat).set(\analysisOn, -1)
Ndef(\wsRepeat).set(\analysisOn, 1)


/*
Notes:

## RTWaveSetAnalysis

+ would be great to have a trigger to turn analysis/recording of material on/off
+ for longer periods of silence: just pause analysis and recording (?)


## RTWaveSetPlayerRepeat
+ Trigger: each time a trigger is received (A trigger occurs when at argument trig that signal changes from negative value to positive value), spawn a sound from the player, following the following parameters:
+	Wave idx (w0)
+	number of included waves (wave idx is first, then the N following)
		(n=4): w0, w1, w2, w3
+	number of repetitions
		could be either interleaved (r=2): w0, w1, w2, w3, w0, w1, w2, w3
		or blocked (r=2): w0, w0, w1, w1, w2, w2, w3, w3
+   playback rate: 1 == normal playback, 1.5 == faster, -0.275 slowly backwards


---

Also great to have:

Intermediate units, which, based on (more or less) high-level parameters, calculate indices:

RTWaveSetDurAmp2Idx.ar(q.aBuf, q.xBuf, dur, amp)
-> amp == -1 : ignore amp
-> dur == -1 : ignore dur

returns index of the wave that is closest to given [dur, amp] combination

RTWaveSetPeakIdx.ar(q.aBuf, q.xBuf, windowSize)

*/