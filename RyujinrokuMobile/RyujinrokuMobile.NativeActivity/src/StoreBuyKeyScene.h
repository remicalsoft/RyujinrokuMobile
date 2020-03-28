#pragma once

#include "Scene.h"
#include "ItemFont.h"
#include <vector>
#include "D_StoreItem.h"

const static int STORE_BARRAGE_KEY_MAX = 100;	//この値を変更したらセーブデータのバージョンを変えて引き継ぎをすること

class StoreBuyKeyScene :
	public Scene
{
	
	int _imgBack;
	std::vector<D_StoreItem*> _infoList;
	std::vector<ItemFont*> _list;
	int _font, _fontSmall;
	int _selectID;

public:
	StoreBuyKeyScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~StoreBuyKeyScene();

	bool update() override;
	void draw() override;

	void disableAll();
};

