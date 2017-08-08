s.boot


(

// create a WavesetData object
var wsData =  WavesetData(server: s);


{
	var newestIdx, oldestIdx, idx;
	var rate = 1;
	var groupSize = MouseX.kr(1, 100);
	var repeat = 10;
	var trig = Dust.ar(50);
	var wRms, wDur;

	#oldestIdx, newestIdx= WavesetAnalysis.ar(wsData, SoundIn.ar(0), 1);

	// select newest WS
	// idx = newestIdx;

	// select waveset according to a specific featureset, -1 disables the feature.
	// idx = WavesetSelector.ar(wsData, dur:-1, rms: 1, peaks: -1, lookBackLimit: -1);

	// select wavest randomly
	idx = WhiteNoise.ar.linlin(-1, 1, oldestIdx, newestIdx);


	// obtain features from waveset

	// is it actually rms? wouldn;t amplitude be better?
	// then one could normalise the waves by multiplying by 1/wAmp
	// also, it should compute the feature for a given range ("groupSize")...
	wRms = WavesetGetFeature.kr(wsData, \rms, idx);//.poll(label:"rms");

	wDur = WavesetGetFeature.kr(wsData, \dur, idx);//.poll(label:"dur");

	// use one of these to resynthesize
	// WavesetSynthContinuous.ar(wsData,idx,  rate, groupSize, 1);
	WavesetSynthTriggered.ar(wsData, trig, idx,  rate, groupSize, 1);

}.play;
)

// sometimes, this results in
//
// RingBuffer::get(7322) Error: Value out of Range! (len=1998,writePos=9321)
// unknown exception in real time
