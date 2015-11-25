Server.killAll;

(
s.waitForBoot{
	// b = Buffer.read(s, "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav",0,-1);
	b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav", 0, -1);
	q = ();
	q.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
	q.xBuf = Buffer.alloc(s, 10 * s.sampleRate, 1);

};
)


(
r{
	Ndef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });

	Ndef(\analysis).addSpec(\analyse, [0, 1, \lin, 1]);
	Ndef(\analysis, {
		var analyse     = \analyse.kr(1);

		RTWaveSetAnalysis.ar(q.aBuf, q.xBuf,
			Ndef(\sound).ar(1),
			analyse
		);
	});
	1.wait;
	// addSpec >> install JITLibExtensions quark
	Ndef(\wsRepeat, {
		var trig, rtIdx;

		trig        = Impulse.ar(\trigRate.kr(1), 0.01);

		// analysis returns idx of last recorded WS
		rtIdx = Ndef(\analysis).ar[0];

		RTWaveSetPlayerTriggered.ar(q.aBuf, q.xBuf,
			0, 1, rtIdx, trig, 0, 1);
	});
	0.5.wait;
	Server.killAll;
}.play;
)
Ndef(\wsRepeat).play;



)



//////////////////////////////////////////
	Server.killAll;
(
s.waitForBoot{
	q = ();
	b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav", 0, -1);
	q.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
	q.xBuf = Buffer.alloc(s, 10 * s.sampleRate, 1);
}
)

(
{
	var idx, output;
	idx = RTWaveSetAnalysis.ar(q.aBuf, q.xBuf,
		PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2),
		1
	);
	output = SinOsc.ar;
	// output = RTWaveSetPlayerTriggered.ar(q.aBuf, q.xBuf,
	// 	0, 1, idx, Impulse.ar(0), 0, 1
	// );
	[idx, output]
}.plot(0.1);
)