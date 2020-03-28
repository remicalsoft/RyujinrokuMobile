#pragma once

#include "Scene.h"
#include "ItemFont.h"
#include <vector>
#include "D_StoreItem.h"
#include "StoreBuyScene.h"


class ItemEquipScene :
	public Scene
{
	
	int _imgBack;
	int _imgCell, _imgTitleCell;
	int _imgCheckBoxOn, _imgCheckBoxOff;
	std::vector<D_StoreItem*> _infoList;
	std::vector<ItemFont*> _list;
	int _font, _fontSmall, _fontBig;
	int _selectID;

public:
	ItemEquipScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~ItemEquipScene();

	bool update() override;
	void draw() override;

	void disableAll();
};

