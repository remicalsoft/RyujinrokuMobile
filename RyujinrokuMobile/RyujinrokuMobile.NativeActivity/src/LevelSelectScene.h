#pragma once

#include "Scene.h"
#include <vector>
#include "LevelItem.h"
#include "ScenePrmBase.h"
#include "Define.h"
#include "ChapterSelector.h"

class LevelSelectScene : public Scene
{
protected:
	int _imgBack;
	int _imgMenuItem[3];
	int _menuItem;
	int _selectID;
	bool _isFinalized, _isCanceled;
	int _counter, _finalizeCounter, _cancelCounter;
	std::vector<LevelItem*> _items;
	eStage _eStage;
	ChapterSelector* _chapterSelector;

	void saveSelectType();

public:
	LevelSelectScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~LevelSelectScene();
	virtual bool initialize() override;
	virtual bool update() override;
	virtual void draw() override;
	bool shouldGoChapterSelector();
};

