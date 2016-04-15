Server.killAll;

(
var wsData;
s.waitForBoot{
	/*
	b = Buffer.read(s, "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav",0,-1);
	*/
	b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav",0,-1,r);
	wsData = RTWavesetData();
	//NdefMixer(s);

};

r={

SynthDef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });

x = SynthDef(\wstest, {
	arg repetition=10, groupSize=10, rate=1, desiredDur=(1), desiredRMS=(-1), analysisOn=1;
	var idx, out, trig;

	RTWavesetAnalysis.ar(wsData, PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2), analysisOn).poll;
desiredDur.poll;
		desiredRMS.poll;
	trig = Dust.ar(10);
	idx = RTWavesetSelector.ar(wsData, 0.1, -1);
	RTWavesetGetFeature.kr(wsData, \rms , idx).poll(label:"rms");
	RTWavesetGetFeature.kr(wsData, \dur, idx).poll(label:"dur");

	out = RTWavesetSynthTriggered.ar(
			wsData, trig, idx-groupSize+1,  rate, groupSize, repetition);
	Out.ar(0,out);


}).play;


}
)

x.set(\desiredDur,-1);
x.set(\desiredRMS,-1);

