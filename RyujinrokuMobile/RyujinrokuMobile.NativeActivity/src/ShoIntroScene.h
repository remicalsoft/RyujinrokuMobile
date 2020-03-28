#pragma once

#include "FadableScene.h"
#include "ISceneChangedListener.h"

class ISceneChangedListener;

class ShoIntroScene : public FadableScene
{

	int _imgBack;
	int _img[2];
	int _selectID;

protected:
	int getFadeTime() override;

public:
	ShoIntroScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~ShoIntroScene();
	bool update() override;
	void draw() override;

};

