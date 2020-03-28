#include "LevelSelectSceneEX.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "SE.h"
#include "GameData.h"
#include "GameScenePrm.h"
#include "MenuSelectUtils.h"
#include "Toast.h"
#include "ChapterData.h"
#include "SelectedData.h"

const static int FINISH_COUNT = 64;

LevelSelectSceneEX::LevelSelectSceneEX(ISceneChangedListener *impl, ScenePrmBase* prm) : LevelSelectScene(impl, prm) {
	_selectID = 1;
}

LevelSelectSceneEX::~LevelSelectSceneEX() {
	for (int i = 0; i < 3; i++) {
		DeleteGraph(_imgMenuItem[i]);
	}
}

bool LevelSelectSceneEX::initialize()
{
	int level = SelectedData::read();
	_selectID = level == -1 ? 1 : level;
	if (_selectID >= 2) {
		_selectID = 1;
	}

	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	LoadDivGraph("dat/image/menu/level/level.png", 3, 1, 3, 513, 188, _imgMenuItem);
	int areaH = 230;
	for (int i = 0; i < 2; i++) {
		_items.push_back(new LevelItem(WIN_W / 2, (WIN_H - areaH * 3) / 2 + areaH*i + 188 / 2, _imgMenuItem[i], i == _selectID ? true : false));
	}
	return true;
}

bool LevelSelectSceneEX::update() {
	_counter++;
	if (!_isFinalized && !_isCanceled) {
		if (Pad::getIns()->get(ePad::down) == 1) {
			_items[_selectID]->disable();
			_selectID = (_selectID + 1) % 2;
			_items[_selectID]->enable();
			SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::up) == 1) {
			_items[_selectID]->disable();
			_selectID = (_selectID + (2 - 1)) % 2;
			_items[_selectID]->enable();
			SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::shot) == 1) {
			bool canDo = true;
			if (_eStage == eStageEX) {
				if(_selectID == 1 && !MenuSelectUtils::canSelectEXStage(eLevel_Normal)) {
					canDo = false;
					Toast::getIns()->add("Normal難易度以上で黎明編をクリアしている必要があります");
				}
			}
			else if (_eStage == eStagePH) {
				if (_selectID==1 && !MenuSelectUtils::canSelectPHStage(eLevel_Normal)) {
					canDo = false;
					Toast::getIns()->add("Normal難易度以上で燦爛編をクリアしている必要があります");
				}
			}
			if (canDo) {
				for (int i = 0; i < _items.size(); i++) {
					_items[i]->finalize();
				}
				GameData::getIns()->level = (eLevel)_selectID;
				_isFinalized = true;
				SE::getIns()->setPlay(eSE::eSE_selectDetail);
			}
			else {
				SE::getIns()->setPlay(eSE::eSE_error);
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
		SelectedData::save(_selectID);
		ChapterData::remove(_eStage, _selectID);
		saveSelectType();
		if (_eStage == eStageEX) {
			GameScenePrm prm(_eStage, (eLevel)_selectID);
			_implSceneChanged->onSceneChanged(eScene::ExOp, false, &prm);
		}
		else {
			GameScenePrm prm(_eStage, (eLevel)_selectID);
			_implSceneChanged->onSceneChanged(eScene::PhOp, false, &prm);
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

void LevelSelectSceneEX::draw() {
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
