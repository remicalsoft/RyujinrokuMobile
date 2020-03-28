#pragma once

#include "FadableScene.h"
#include "LevelItem.h"
#include <vector>
#include "GameScenePrm.h"

class ChapterSelectScene :
	public FadableScene
{
	int _img[3];
	int _imgBack;
	std::vector<LevelItem> _itemList;
	bool _isYes;
	GameScenePrm* _prm;
protected:
	int getFadeTime();
public:
	ChapterSelectScene(ISceneChangedListener* impl, ScenePrmBase* prm);
	~ChapterSelectScene();
	bool update() override;
	void draw() override;
};

