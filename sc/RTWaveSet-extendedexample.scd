Server.killAll;

(
s.waitForBoot{
	/*
	b = Buffer.read(s, "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav",0,-1);
	*/
	b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav",0,-1,r);
	q = ();
	q.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
	q.xBuf = Buffer.alloc(s, 10 * s.sampleRate, 1);
	//NdefMixer(s);

};

r={

SynthDef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });

x = SynthDef(\wstest, {
	arg repetition=10, groupSize=10, rate=1, desiredDur=(1), desiredRMS=(-1), analysisOn=1;
	var idx, out, trig;

	RTWaveSetAnalysis.ar(q.aBuf, q.xBuf, PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2), analysisOn).poll;
desiredDur.poll;
		desiredRMS.poll;
	trig = Dust.ar(10);
	idx = RTWaveSetSelector.ar(q.aBuf, q.xBuf, 0.1, -1);
	RTWaveSetFeatureExtractor.kr(q.aBuf, q.xBuf, \rms , idx).poll(label:"rms");
	RTWaveSetFeatureExtractor.kr(q.aBuf, q.xBuf, \dur, idx).poll(label:"dur");

	out = RTWaveSetPlayerTriggered.ar(
			q.aBuf, q.xBuf, trig, idx-groupSize+1,  rate, groupSize, repetition);
	Out.ar(0,out);


}).play;


}
)

x.set(\desiredDur,-1);
x.set(\desiredRMS,-1);

