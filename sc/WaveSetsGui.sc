(

var createSlider = {
	arg win, x, y, labelText, valAction, defaultVal=0.0;

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

// create GUI
s.waitForBoot({

	var grainPlay;
	var win;
	var playDirect;
	var playGrain;
	var directButton;
	var grainButton;
	var holdButton;
	var wsData;
	var repAction;

	SynthDef(\WSRepeat, {
		arg rep=5, numWS=1, xingIdx=(-1), hold=0, idxOffset=0;
		var idx, out;

		wsData = ();
		wsData.aBuf = Buffer.alloc(s, 100 * s.sampleRate, 1);
		wsData.xBuf = Buffer.alloc(s, 100000, 1);
		wsData.idxBus = Bus.audio(s);

		idx = RTWaveSetAnalysis.ar(wsData.aBuf,wsData.xBuf,SoundIn.ar(1));
		out = RTWaveSetPlayerRepeat.ar(wsData.aBuf,wsData.xBuf,rep,numWS,idx,hold,idxOffset);
		Out.ar(0, out);


	}).add;

	win = Window.new("RT WaveSets", Rect(200,200,400,200));

	directButton = Button.new(win,Rect(10,10,80,30)).states_([["Direct Off"],["Direct On"]]);
	directButton.action = { if(directButton.value.asBoolean,
		{ playDirect = { SoundIn.ar([0, 1]) }.play},
		{ playDirect.release }) };

	grainButton = Button.new(win,Rect(10,55,80,30)).states_([["WS Off"],["WS On"]]);
	grainButton.action = { if(grainButton.value.asBoolean,
		{
			playGrain = Synth(\WSRepeat);
			playGrain.set(\rep,1);
			playGrain.set(\numWS,1);
		},
		{ playGrain.free }) };



	createSlider.value(win,90,85,"repeats",{
		arg val,lbl;
		val = round(val*19+1);
		lbl.string = val;
		playGrain.set(\rep,val);
	});

	createSlider.value(win,90,115,"context",{
		arg val,lbl;
		val = round(val*19+1);
		lbl.string = val;
		playGrain.set(\numWS,val);
	});

	holdButton = Button.new(win,Rect(140,145,80,30)).states_([["Hold Off"],["Hold On"]]);
	holdButton.action = {
		playGrain.set(\hold,holdButton.value);
	};

	createSlider.value(win,90,175,"Offset",{
		arg val,lbl;
		var val2;
		val2 = round((val*100)-100);
		lbl.string = val2;
		playGrain.set(\idxOffset,val2);
	},1);

	win.front;

});
)