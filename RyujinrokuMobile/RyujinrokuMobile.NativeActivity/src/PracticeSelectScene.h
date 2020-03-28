#pragma once
#include "Scene.h"
#include <vector>
#include "LevelItem.h"
#include "ScenePrmBase.h"

//各ステージ練習のためのセレクト画面
class PracticeSelectScene : public Scene
{
	const static int NUM = 5;

	int _imgBack;
	int _menuItem;
	int _stageSelectID;
	int _levelSelectID;
	bool _isFinalized, _isCanceled;
	int _counter, _finalizeCounter, _cancelCounter;
	std::vector<LevelItem*> _items;
	int _isActivated;
	int _imgStage[NUM];
public:
	PracticeSelectScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~PracticeSelectScene();
	bool update() override;
	void draw() override;
	void onResume();
};

