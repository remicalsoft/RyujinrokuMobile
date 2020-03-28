#pragma once
#include "Scene.h"
#include <vector>
#include "ScenePrmBase.h"

class StoryPreGameScene : public Scene
{
	std::vector<int> _imgList;
	int _imgN;
	int _counter;
	int _imgBackground, _imgTxtBack;
	int _charN;
	int _font, _font2, _txtColor;
public:
	StoryPreGameScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~StoryPreGameScene();
	bool update() override;
	void draw() override;
};

