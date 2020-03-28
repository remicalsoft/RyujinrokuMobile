#pragma once

#include "FadableScene.h"
#include "ISceneChangedListener.h"

class ISceneChangedListener;

class ContinueScene : public FadableScene
{

	int _img;
	int _counter;
	int _imgW, _imgH;

protected:
	int getFadeTime() override;

public:
	ContinueScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~ContinueScene();
	bool update() override;
	void draw() override;

};

