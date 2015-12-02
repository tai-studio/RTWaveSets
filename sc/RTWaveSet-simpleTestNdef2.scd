Server.killAll;

(
s.waitForBoot{
	/*
	b = Buffer.read(s, "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav",0,-1);
	*/
	b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav",0,-1,f);
	q = ();
	q.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
	q.xBuf = Buffer.alloc(s, 10 * s.sampleRate, 1);
	NdefMixer(s);

};
)


(

Ndef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });

Ndef(\wsAnalysis).addSpec(\analysisOn, [-1, 1]);
Ndef(\wsRepeat).addSpec(\repetition, [1, 100]);
Ndef(\wsRepeat).addSpec(\groupSize, [1, 100]);
Ndef(\wsRepeat).addSpec(\trigRate, [1, 100, \lin, 1]);
Ndef(\wsRepeat).addSpec(\rate, [-2, 2]);
Ndef(\wsRepeat).addSpec(\desiredLen, [-1, 10]);
Ndef(\wsRepeat).addSpec(\desiredAmp, [-1, 1]);


Ndef(\wsAnalysis, {
	arg analysisOn=1;
	var idx, idx2, out, trig;
	trig = Impulse.ar(\trigRate.kr(1));

	RTWaveSetAnalysis.ar(q.aBuf, q.xBuf, Ndef(\sound).ar(1), analysisOn);

});


Ndef(\wsRepeat, {
	arg repetition=10, groupSize=10, rate=1, desiredLen=(-1), desiredAmp=(-1);
	var idx, idx2, out, trig;
	trig = Impulse.ar(\trigRate.kr(1));

	idx = RTWaveSetSelector.ar(q.aBuf, q.xBuf, desiredLen, desiredAmp);

	// ^this.multiNew('audio', audioBuf, wsBuf, trig, idx, rate, groupSize, repeat)
	RTWaveSetPlayerTriggered.ar(
		q.aBuf, q.xBuf, trig, idx-groupSize+1,  rate, groupSize, repetition);
}).play;

)

