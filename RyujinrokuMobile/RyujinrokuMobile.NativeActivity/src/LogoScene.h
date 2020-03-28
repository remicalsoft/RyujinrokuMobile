#pragma once

#include "FadableScene.h"
#include "ISceneChangedListener.h"

class ISceneChangedListener;

class LogoScene : public FadableScene
{

	int _img;
	int _counter;
	int _imgW, _imgH;

protected:
	int getFadeTime() override;

public:
	LogoScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~LogoScene();
	bool update() override;
	void draw() override;

};

