


(

var wsData =  RTWavesetData.new;

{
	var idx,idx2;
	var rate = 1;
	var groupSize = 1;
	var repeat = 10;
	var trig = Dust.ar(50);

	#idx,idx2 = RTWavesetAnalysis.ar(wsData, SinOsc.ar(430.66*1), 1);
	//idx2 = RTWavesetSelector(wsData, idx,RTWavesetFeatureRMS,desiredRMS,RTWavesetFeatureLength,desiredLen);

	//idx = RTWavesetSelector.ar(q.aBuf, q.xBuf, -1, 1);
	//RTWavesetGetFeature.kr(q.aBuf, q.xBuf, \rms , idx).poll(label:"rms");
	//RTWavesetGetFeature.kr(q.aBuf, q.xBuf, \dur, idx).poll(label:"dur");
	RTWavesetSynthContinuous.ar(wsData,idx2,  rate, groupSize, 1);
	//RTWavesetSynthTriggered.ar(wsData, trig, idx,  rate, groupSize, 1);

}.play;
)

