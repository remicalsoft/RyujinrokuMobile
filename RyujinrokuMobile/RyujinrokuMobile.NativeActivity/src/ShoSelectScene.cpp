#include "ShoSelectScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "SE.h"
#include "GameData.h"
#include "GameScenePrm.h"
#include "MenuSelectUtils.h"
#include "Toast.h"

const static int FINISH_COUNT = 32;

ShoSelectScene::ShoSelectScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl) {
	_isFinalized = false;
	_isCanceled = false;
	_counter = 0;
	_finalizeCounter = 0;
	_cancelCounter = 0;
	int imgs[CELL_N];
	_selectID = 0;
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_imgShoIntroItem = LoadGraph("dat/image/menu/shoIntro.png");
	load();
}

ShoSelectScene::~ShoSelectScene() {
	for (int i = 0; i < _items.size(); i++) {
		delete _items[i];
	}
	for (int i = 0; i < CELL_N; i++) {
		DeleteGraph(_imgMenuItem[i]);
	}
	DeleteGraph(_imgBack);
	DeleteGraph(_imgShoIntroItem);
}

void ShoSelectScene::load() {
	LoadDivGraph("dat/image/menu/sho.png", 3, 1, 3, 500, 200, _imgMenuItem);
	_items.push_back(new LevelItem(WIN_W / 2, 240, _imgMenuItem[0], _selectID == 0 ? true : false));
	_items.push_back(new LevelItem(WIN_W / 2, 480, _imgMenuItem[1], _selectID == 1 ? true : false));
	_items.push_back(new LevelItem(WIN_W / 2, 720, _imgMenuItem[2], _selectID == 2 ? true : false));
	_items.push_back(new LevelItem(300, 900, _imgShoIntroItem, false));
}

bool ShoSelectScene::update() {
	const static int N = CELL_N + 1;
	_counter++;
	if (!_isFinalized && !_isCanceled) {
		if (Pad::getIns()->get(ePad::down) == 1) {
			_items[_selectID]->disable();
			_selectID = (_selectID + 1) % N;
			_items[_selectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::up) == 1) {
			_items[_selectID]->disable();
			_selectID = (_selectID + (N - 1)) % N;
			_items[_selectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::shot) == 1) {
			bool canDo = true;
			if (_selectID == 1 || _selectID == 2) {
				if (_selectID == 1){
					if (!(MenuSelectUtils::canSelectEXStage(eLevel_Easy) || MenuSelectUtils::canSelectEXStage(eLevel_Normal))) {
						canDo = false;
						Toast::getIns()->add("黎明編をクリアすると選択可能になります");
					}
				}
				else if(_selectID == 2) {
					if (!(MenuSelectUtils::canSelectPHStage(eLevel_Easy) || MenuSelectUtils::canSelectPHStage(eLevel_Normal))) {
						canDo = false;
						Toast::getIns()->add("燦爛編をクリアすると選択可能になります");
					}
				}
			}
			if (_selectID == 3) {
				_implSceneChanged->onSceneChanged(eScene::ShoIntro, true, nullptr);
				SE::getIns()->setPlay(eSE::eSE_select);
				return true;
			}
			if (canDo) {
				for (int i = 0; i < _items.size(); i++) {
					_items[i]->finalize();
				}
				_isFinalized = true;
				SE::getIns()->setPlay(eSE::eSE_select);
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
		_finalizeCounter = 0;
		_isFinalized = false;
		_counter = 0;
		for (int i = 0; i < _items.size(); i++) {
			delete _items[i];
		}
		_items.clear();

		load();

		GameScenePrm prm;
		switch (_selectID) {
		case 0:
			prm._stage = eStage1;
			_implSceneChanged->onSceneChanged(eScene::LevelSelect, true, &prm);
			break;
		case 1:
			prm._stage = eStageEX;
			_implSceneChanged->onSceneChanged(eScene::LevelSelectEX, true, &prm);
			break;
		case 2:
			prm._stage = eStagePH;
			_implSceneChanged->onSceneChanged(eScene::LevelSelectEX, true, &prm);
			break;
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

void ShoSelectScene::draw() {
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
