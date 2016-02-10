


(

var wsData =  RTWaveSetData.new;

{
	var idx,idx2;
	var rate = 3.0;
	var groupSize = 10;
	var repeat = 10;
	var trig = Dust.ar(50);

	#idx,idx2 = RTWaveSetAnalysis.ar(wsData, SoundIn.ar(0), 1);
	//idx2 = RTWaveSetSelector(wsData, idx,RTWaveSetFeatureRMS,desiredRMS,RTWaveSetFeatureLength,desiredLen);

	//idx = RTWaveSetSelector.ar(q.aBuf, q.xBuf, -1, 1);
	//RTWaveSetFeatureExtractor.kr(q.aBuf, q.xBuf, \rms , idx).poll(label:"rms");
	//RTWaveSetFeatureExtractor.kr(q.aBuf, q.xBuf, \dur, idx).poll(label:"dur");
	RTWaveSetPlayerContinuous.ar(wsData,idx2,  rate, groupSize, 1);
	//RTWaveSetPlayerTriggered.ar(wsData, trig, idx,  rate, groupSize, 1);

}.play;
)

