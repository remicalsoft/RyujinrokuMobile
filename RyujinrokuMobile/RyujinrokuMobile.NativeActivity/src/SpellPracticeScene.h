#pragma once

#include "Scene.h"
#include <vector>
#include "LevelItem.h"
#include "ScenePrmBase.h"
#include "BossPrm.hpp"

//各ステージ練習のためのセレクト画面
class SpellPracticeScene : public Scene
{
	int _imgBack;
	int _menuItem;
	int _stageSelectID;
	int _spellSelectID;
	bool _isFinalized, _isCanceled;
	int _counter, _finalizeCounter, _cancelCounter;
	std::vector<BaseEffectItem*> _items;
	int _isActivated;
	int _levelGraph[eLevel_Num];

	int _font[3];
//	int _spellnameGraph[eStage_Num][MAXSPELLNUM_PER_STAGE];
	std::vector<int> _handleList;
public:
	SpellPracticeScene(ISceneChangedListener *impl, ScenePrmBase* prm);	
	~SpellPracticeScene();
	bool update() override;
	void draw() override;
	void onResume();

	void makeItemGraph();
	void deleteItemGraph();
	void rewriteItemGraph();
	int getItemHandle();
	int getSpellNameHandle();
	int getMAXSpellNumStage();
	int getCursolX(int level);	//難易度の左上の座標を返す
	int getCursolY(int spellnum);	//弾幕番号の左上の座標を返す
	void updateTarget();
};

