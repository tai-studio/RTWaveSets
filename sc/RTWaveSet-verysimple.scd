


(

var wsData =  RTWavesetData.new;

{
	var idx,idx2;
	var rate = 1;
	var groupSize = 1;
	var repeat = 10;
	var trig = Dust.ar(50);

	#idx,idx2 = WavesetAnalysis.ar(wsData, SinOsc.ar(430.66*1), 1);
	//idx2 = WavesetSelector(wsData, idx,RTWavesetFeatureRMS,desiredRMS,RTWavesetFeatureLength,desiredLen);

	//idx = WavesetSelector.ar(q.aBuf, q.xBuf, -1, 1);
	//WavesetGetFeature.kr(q.aBuf, q.xBuf, \rms , idx).poll(label:"rms");
	//WavesetGetFeature.kr(q.aBuf, q.xBuf, \dur, idx).poll(label:"dur");
	WavesetSynthContinuous.ar(wsData,idx2,  rate, groupSize, 1);
	//WavesetSynthTriggered.ar(wsData, trig, idx,  rate, groupSize, 1);

}.play;
)

