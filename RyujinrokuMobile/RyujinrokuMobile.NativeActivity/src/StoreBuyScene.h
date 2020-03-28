#pragma once

#include "Scene.h"
#include "ItemFont.h"
#include <vector>
#include "D_StoreItem.h"

const static int STORE_EQUIPABLEITEM_MAX = 100;	//この値を変更したらセーブデータのバージョンを変えて引き継ぎをすること

enum eEquipItem {
	eEquipItem_Dress,
	eEquipItem_Ring,
	eEquipItem_Ring2,
	eEquipItem_Hoseki,
	eEquipItem_Hoseki2,
	eEquipItem_Jacket,
	eEquipItem_Jacket2,
	eEquipItem_Pheromone,
	eEquipItem_Pheromone2,
	eEquipItem_Soul,
	eEquipItem_Soul2,
	eEquipItem_Bomb,
	eEquipItem_Bomb2,
	eEquipItem_Tsubo,

	eEquipItem_Num,
};

class StoreBuyScene :
	public Scene
{
	
	int _imgBack;
	int _imgCell, _imgTitleCell;
	int _imgSoldout;
	std::vector<D_StoreItem*> _infoList;
	std::vector<ItemFont*> _list;
	int _font, _fontSmall;
	int _selectID;

public:
	StoreBuyScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~StoreBuyScene();

	bool update() override;
	void draw() override;

	void disableAll();
};

