#pragma once
#include "Scene.h"
#include <vector>
#include "LevelItem.h"
#include "ScenePrmBase.h"

class ShoSelectScene : public Scene
{
	const static int CELL_N = 3;

	int _imgBack;
	int _menuItem;
	int _selectID;
	bool _isFinalized, _isCanceled;
	int _counter, _finalizeCounter, _cancelCounter;
	int _imgMenuItem[CELL_N];
	int _imgShoIntroItem;
	std::vector<LevelItem*> _items;

	void load();

public:
	ShoSelectScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~ShoSelectScene();
	bool update() override;
	void draw() override;
};

