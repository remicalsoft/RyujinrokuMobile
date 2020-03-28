#pragma once
#include "Scene.h"
#include <vector>
#include "MenuItem.h"
#include "ScenePrmBase.h"
#include "ShineLineMgr.h"
#include "MusicMgr.h"

class MenuScene : public Scene
{
	enum eItem {
		eGame,
		ePractice,
		eBarrage,
		eShop,
		eReplay,
		eStory,
		eMusic,
		eScore,
		eConfig,
		eEnd,
		eNum,
	};

	int _imgBack, _imgBackShine;
    int _imgPremium;
	int _menuItem;
	int _font;
	int _selectID;
	int _brightnessBackShine;
	bool _isFinalized;
	int _counter, _finalizeCounter;
	int _imgMenuItem[eItem::eNum];
	MusicMgr *_musicMgr;
	std::vector<MenuItem*> _items;
	std::vector<int> _imgItems;
	void finalizeItems();
	ShineLineMgr _shineLineMgr;

public:
	MenuScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~MenuScene();
	bool update() override;
	void draw() override;

	MusicMgr* getmusicMgr(){return _musicMgr;}
};

