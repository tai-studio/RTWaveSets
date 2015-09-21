(
var initGUI;

var createSlider = {
	arg win, x, y, labelText, defaultVal, valAction;

	var view, slider, label;
	view = CompositeView.new(win,Rect(x,y,320,30));
	StaticText.new(view,Rect(0,0,80,30)).string_(labelText);
	slider = Slider.new(view,Rect(50,0,160,30));
	label = StaticText.new(view,Rect(210,0,80,30));
	slider.action = {
		arg ez;
		valAction.value(ez.value,label);
	};
	slider.valueAction=defaultVal;

	slider
};


initGUI = {

	var grainPlay;
	var win;
	var playDirect;
	var directButton;
	var analysisOnButton;
	var wsTriggerButton;
	var holdButton;
	var wsData;
	var repAction;

	Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav",0,-1,{
		arg buffer;
		Ndef(\sound, {	PlayBuf.ar(buffer.numChannels, buffer.bufnum, BufRateScale.kr(buffer.bufnum), loop: 2); });

		wsData = ();
		wsData.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
		wsData.xBuf = Buffer.alloc(s, 100000, 1);

		Ndef(\wsRepeat, {
			arg t_trig=0, repetition=10, numWS=20, xingIdx=(-1), idxOffset=0, analysisOn=1, rate=1, desiredLen=(-1);
			var idx, idx2, out, trig;

			idx = RTWaveSetAnalysis.ar(wsData.aBuf, wsData.xBuf, Ndef(\sound).ar(1), analysisOn);
			idx2 = RTWaveSetSelector.ar(wsData.aBuf, wsData.xBuf, desiredLen);

			RTWaveSetPlayerRepeat.ar(
				wsData.aBuf, wsData.xBuf, repetition, numWS, idx2-numWS+1, T2A.ar(t_trig), idxOffset, rate
			);
		});

		Ndef(\wsRepeat).play;
	});

	win = Window.new("RT WaveSets", Rect(200,200,360,170));

	directButton = Button.new(win,Rect(10,10,80,30)).states_([["Direct Off"],["Direct On"]]);
	directButton.action = { if(directButton.value.asBoolean,
		{ playDirect = { Ndef(\sound).ar(1) }.play},
		{ playDirect.release }) };

	analysisOnButton = Button.new(win,Rect(10,55,80,30)).states_([["Analysis On"],["Analysis Off"]]);
	analysisOnButton.action = { if(analysisOnButton.value.asBoolean,
		{ Ndef(\wsRepeat).set(\analysisOn, -1) },
		{ Ndef(\wsRepeat).set(\analysisOn, 1) }) };
	analysisOnButton.action.value;

	wsTriggerButton = Button.new(win,Rect(10,55+45,80,30)).states_([["WS Trigger"]]);
	wsTriggerButton.action = {
		Ndef(\wsRepeat).set(\t_trig, 1);
		};

	createSlider.value(win,100,10,"repeats",0.1,{
		arg val,lbl;
		val = round(val*99+1);
		lbl.string = val;
		Ndef(\wsRepeat).set(\repetition,val);
	});

	createSlider.value(win,100,40,"numWS",0.1,{
		arg val,lbl;
		val = round(val*19+1);
		lbl.string = val;
		Ndef(\wsRepeat).set(\numWS,val);
	});

	createSlider.value(win,100,70,"Offset",1,{
		arg val,lbl;
		var val2;
		val2 = round((val*100)-100);
		lbl.string = val2;
		Ndef(\wsRepeat).set(\idxOffset,val2);
	});

	createSlider.value(win,100,100,"Rate",0.75,{
	arg val,lbl;
		var val2;
		val2 = round(((val*4)-2)*10)/10;
		lbl.string = val2;
		Ndef(\wsRepeat).set(\rate,val2);
	});

	createSlider.value(win,100,130,"Length",0,{
	arg val,lbl;
		var val2;
		val2 = round((val*100))/10;
		if(val2==0,{
			lbl.string = "OFF";
			val2=(-1);
		},{
			lbl.string = format("% ms",val2);
		});

		Ndef(\wsRepeat).set(\desiredLen, val2);
	});

	win.front;

};

// create GUI
s.waitForBoot(initGUI);

)