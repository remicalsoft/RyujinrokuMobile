#pragma once
#include "Scene.h"
#include <vector>
#include "LevelItem.h"
#include "ScenePrmBase.h"
#include "Define.h"
#include "LevelSelectScene.h"

class LevelSelectSceneEX : public LevelSelectScene
{
	int _imgMenuItem[3];
public:
	LevelSelectSceneEX(ISceneChangedListener *impl, ScenePrmBase* prm);
	~LevelSelectSceneEX();
	bool initialize() override;
	bool update() override;
	void draw() override;
};

