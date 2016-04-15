Server.killAll;

(

s.waitForBoot{

	var srcFile = "/Volumes/Fabi HD/Dropbox/5MA/Wavesets/Audiosamples/flute.wav";
	//var srcFile = Platform.resourceDir +/+ "sounds/a11wlk01.wav";
	//var srcFile = "/localvol/workshops-lehre/2015-mlabHelsinki/squeaky_shoe_and_fifth_floor_office_chair.wav";

	b = Buffer.read(s, srcFile,0,-1,r);


	//b = Buffer.read(s, "/Volumes/Fabi HD/Music/Christian Löffler/Young Alaska/03 Notes (Original Mix).wav",0,-1,r);
	q = WavesetData(10000000,30000);
	NdefMixer(s);

};

r={


Ndef(\sound, {	PlayBuf.ar(b.numChannels, b.bufnum, BufRateScale.kr(b.bufnum), loop: 2); });

Ndef(\wsAnalysis).addSpec(\analysisOn, [-1, 1, \lin, 1]);
Ndef(\wsRepeat).addSpec(\repetition, [1, 100, \lin, 1]);
Ndef(\wsRepeat).addSpec(\groupSize, [1, 100, \lin, 1]);
Ndef(\wsRepeat).addSpec(\trigRate, [0, 100, \lin, 1]);
Ndef(\wsRepeat).addSpec(\rate, [-2, 2]);
Ndef(\wsRepeat).addSpec(\desiredLen, [-1, 10]);
Ndef(\wsRepeat).addSpec(\desiredRMS, [-1, 1]);
Ndef(\wsRepeat).addSpec(\desiredPeaks, [-1, 100, \lin, 1]);
Ndef(\wsRepeat).addSpec(\selLookBack, [-1, 1000, \lin, 1]);
Ndef(\wsRepeat).addSpec(\idxOffset, [-100, 2000, \lin, 1]);
Ndef(\wsRepeat).addSpec(\randBack, [0, 2000, \lin, 1]);

Ndef(\wsAnalysis, {
	arg analysisOn=1;
	var idxStart,idxEnd;
	WavesetAnalysis.ar(q, Ndef(\sound).ar(1), analysisOn);
});


Ndef(\wsRepeat, {
		arg repetition=1, groupSize=100, rate=1, desiredLen=(-1), desiredRMS=(-1), desiredPeaks=(-1), selLookBack=(-1), idxOffset=0, randBack=0;
		var idx, idx2, out, trig, trig2, rms, idxRange;

		//idxRange = WavesetAnalysis.ar(q, Ndef(\sound).ar(1));

		trig = Impulse.ar(\trigRate.kr(1));
		//idxRange.poll(trig);
		//trig = Impulse.ar(EnvGen.ar(Env.perc, trig, 100,0,0.5)); // try to create "clouds"

		idx = WavesetSelector.ar(q, desiredLen/1000, desiredRMS, desiredPeaks ,selLookBack);
		//idx.poll(trig);
		//rms = WavesetGetFeature.kr(q, \dur, idx);
		//rms.poll;

		WavesetGetFeature.kr(q, \peaks, idx).poll;
		out = WavesetSynthTriggered.ar(q, trig, idx+TIRand.ar(0,randBack,trig)+idxOffset,  rate, groupSize, repetition);

		//out = DC.ar(0);
		//trig = out;
		//*EnvGen.ar(Env.sine, trig, 1,0,K2A.ar(dur)); // try envelope
		//Ndef(\sound).ar(1)*EnvGen.ar(Env.sine, trig, 1,0,1); // envelope tryouts

		//out = WavesetSynthContinuous.ar(q, idxRange[1],  rate, groupSize, repetition);

		Out.ar(0,Pan2.ar(out));

}).play;

}
)

