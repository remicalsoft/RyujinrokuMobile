#pragma once
#include "Scene.h"
#include "Pad.h"

class ConfigScene : public Scene{
	const static int PAD_MAX = 16;
	int _imgTitle;
	int _imgBack;
	int _imgConfig;
	int _fontA,_fontB;
	int _colorFocus;
	int _colorOther;
	int _colorBack;
	int _colorFront;
	int _configStep;
	int _xFlag[PAD_MAX-4];
//	int _pad_dum[5];
	PadID _pad_dum;
	int _count[PAD_MAX];

	bool _isCanceled;
	int _counter, _cancelCounter;
	int _debugCommandStatus;

public:
	ConfigScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~ConfigScene();
	void draw();
	bool update();
	void updateDebugCommand();
	void saveConfig();
};