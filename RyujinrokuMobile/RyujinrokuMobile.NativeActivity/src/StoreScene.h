#pragma once

#include "Scene.h"
#include "ItemFont.h"
#include <vector>

class StoreScene :
	public Scene
{
	
	int _imgBack;
	std::vector<ItemFont*> _list;
	int _font;
	int _selectID;

public:
	StoreScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~StoreScene();

	bool update() override;
	void draw() override;

	void disableAll();
};

