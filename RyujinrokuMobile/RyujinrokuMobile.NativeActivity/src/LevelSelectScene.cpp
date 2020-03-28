#include "LevelSelectScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "SE.h"
#include "GameData.h"
#include "GameScenePrm.h"
#include "ChapterData.h"
#include "SavedData.h"
#include "SelectedData.h"
#include "Toast.h"

const static int FINISH_COUNT = 64;

void LevelSelectScene::saveSelectType()
{
	switch (_eStage) {
	case eStage1:
		switch (_selectID) {
		case eLevel_Easy:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Easy_1]++;
			break;
		case eLevel_Normal:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Normal_1]++;
			break;
		case eLevel_Hard:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Hard_1]++;
			break;
		}
		break;
	case eStageEX:
		switch (_selectID) {
		case eLevel_Easy:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Easy_EX]++;
			break;
		case eLevel_Normal:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Normal_EX]++;
			break;
		}
	case eStagePH:
		switch (_selectID) {
		case eLevel_Easy:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Easy_PH]++;
			break;
		case eLevel_Normal:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Normal_PH]++;
			break;
		}
	}
}

LevelSelectScene::LevelSelectScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl) {
	GameScenePrm* p = dynamic_cast<GameScenePrm*>(prm);
	_eStage = p->_stage;
	_isFinalized = false;
	_isCanceled = false;
	_counter = 0;
	_finalizeCounter = 0;
	_cancelCounter = 0;
	_chapterSelector = nullptr;
}

LevelSelectScene::~LevelSelectScene() {
	for (int i = 0; i < _items.size(); i++) {
		if (_items[i] != nullptr) {
			delete _items[i];
		}
		_items[i] = nullptr;
	}
	for (int i = 0; i < 3; i++) {
		DeleteGraph(_imgMenuItem[i]);
	}
	DeleteGraph(_imgBack);
}

bool LevelSelectScene::initialize()
{
	int level = SelectedData::read();
	_selectID = level==-1 ? 1 : level;
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	LoadDivGraph("dat/image/menu/level/level.png", 3, 1, 3, 513, 188, _imgMenuItem);
	int areaH = 230;
	for (int i = 0; i < 3; i++) {
		_items.push_back(new LevelItem(WIN_W / 2, (WIN_H - areaH * 3) / 2 + areaH*i + 188 / 2, _imgMenuItem[i], i == _selectID ? true : false));
	}
	return true;
}

bool LevelSelectScene::update() {
	_counter++;
	if (!_isFinalized && !_isCanceled) {
		if (Pad::getIns()->get(ePad::down) == 1) {
			_items[_selectID]->disable();
			_selectID = (_selectID + 1) % LEVEL_NUM;
			_items[_selectID]->enable();
			SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::up) == 1) {
			_items[_selectID]->disable();
			_selectID = (_selectID + (LEVEL_NUM - 1)) % LEVEL_NUM;
			_items[_selectID]->enable();
			SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::shot) == 1) {
			for (int i = 0; i < _items.size(); i++) {
				_items[i]->finalize();
			}
			_isFinalized = true;
			if (shouldGoChapterSelector()) {
				SE::getIns()->setPlay(eSE::eSE_select);
			}
			else {
				SE::getIns()->setPlay(eSE::eSE_selectDetail);
			}
		}
		if (Pad::getIns()->get(ePad::bom) == 1) {
			SE::getIns()->setPlay(eSE::eSE_cancel);
			for (int i = 0; i < _items.size(); i++) {
				_items[i]->cancel();
			}
			_isCanceled = true;
		}
	}
	if (_isFinalized) {
		_finalizeCounter++;
	}
	if (_finalizeCounter == FINISH_COUNT) {
		for (auto item : _items) {
			delete item;
		}
		_items.clear();
		_finalizeCounter = 0;
		_isFinalized = false;
		_counter = 0;

		saveSelectType();
		SelectedData::save(_selectID);

		GameScenePrm prm(_eStage, (eLevel)_selectID);
		if (shouldGoChapterSelector()) {
			_implSceneChanged->onSceneChanged(eScene::SelectChapter, true, &prm);
		}
		else {
			ChapterData::remove(_eStage, _selectID);
			_implSceneChanged->onSceneChanged(eScene::Op, false, &prm);
		}
		return false;
	}
	if (_isCanceled) {
		_cancelCounter++;
	}
	if (_cancelCounter == FINISH_COUNT/2) {
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
		return false;
	}
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->update();
	}
	return true;
}

void LevelSelectScene::draw() {
	bool isBrended = false;
	DrawGraph(0, 0, _imgBack, FALSE);
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->draw();
	}
	if (_counter < 32) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - _counter * 8);
		isBrended = true;
	}
	if (_finalizeCounter > 16) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (_finalizeCounter - 16) * 16);
		isBrended = true;
	}
	if (_cancelCounter > 16) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (_cancelCounter - 16) * 16);
		isBrended = true;
	}
	if (isBrended) {
		DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

bool LevelSelectScene::shouldGoChapterSelector()
{
	ChapterData* data = ChapterData::read(_eStage, _selectID);
	if (data != nullptr) {
		eLevel level = (eLevel)_selectID;
		if (data->level == level) {
			return true;
		}
	}
	return false;
}
