#include "PracticeSelectScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "SE.h"
#include "GameData.h"
#include "MenuScenePrm.h"
#include "BgmLoopPosDefine.h"
#include "GameScenePrm.h"
#include "BGM.h"
#include "Image.h"
#include "MenuSelectUtils.h"
#include "Toast.h"
#include "SavedData.h"


//大体StorySelectSceneからコピペ
const static int FINISH_COUNT = 64;

PracticeSelectScene::PracticeSelectScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl) {
	_isFinalized = false;
	_isCanceled = false;
	_isActivated = false;
	_counter = 0;
	_finalizeCounter = 0;
	_cancelCounter = 0;
	_stageSelectID = 0;
	_levelSelectID = 1;
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	LoadDivGraph("dat/image/menu/prctice_stage.png", NUM, 1, NUM, 239, 100, _imgStage);
	for (int i = 0; i < NUM; i++) {
		_items.push_back(new LevelItem(WIN_W/2, (WIN_H-131* NUM)/2 + 131*i + 131/2, _imgStage[i], i==_stageSelectID ? true : false));	//初期選択部分だけ点灯フラグを立てる
	}
	int imgW = 0, imgH = 0;
	GetGraphSize(Image::getIns()->level[0], &imgW, &imgH);
	for (int i = 0; i < eLevel_Num; i++) {
		_items.push_back(new LevelItem(WIN_W/2 + (i-1)*imgW*2, 50, Image::getIns()->level[i], i==_levelSelectID ? true : false));
	}
}

PracticeSelectScene::~PracticeSelectScene() {
	for (int i = 0; i < _items.size(); i++) {
		delete _items[i];
	}
	DeleteGraph(_imgBack);
	for (int i = 0; i < NUM; i++) {
		DeleteGraph(_imgStage[i]);
	}
}

bool PracticeSelectScene::update() {
	if (!_isActivated) {
		onResume();
		_isActivated = true;
	}
	_counter++;
	if (!_isFinalized && !_isCanceled) {
		//上下でステージ選択
		if (Pad::getIns()->get(ePad::down) == 1) {
			_items[_stageSelectID]->disable();
			_stageSelectID = (_stageSelectID + 1) % NUM;
			_items[_stageSelectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::up) == 1) {
			_items[_stageSelectID]->disable();
			_stageSelectID = (_stageSelectID + (NUM - 1)) % NUM;
			_items[_stageSelectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		//左右で難易度選択
		if (Pad::getIns()->get(ePad::right) == 1) {
			_items[NUM +_levelSelectID]->disable();
			_levelSelectID = (_levelSelectID + 1) % eLevel_Num;
			_items[NUM +_levelSelectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::left) == 1) {
			_items[NUM +_levelSelectID]->disable();
			_levelSelectID = (_levelSelectID + (eLevel_Num - 1)) % eLevel_Num;
			_items[NUM +_levelSelectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::shot) == 1) {
			bool canDo = true;
			if (_stageSelectID!=0 && !MenuSelectUtils::canSelectPracticeStage(_levelSelectID,_stageSelectID)) {
				canDo = false;
				Toast::getIns()->add("前の章をクリアしている必要があります");
			}
			if (canDo) {
				for (int i = 0; i < _items.size(); i++) {
					_items[i]->finalize();
				}
				//			GameData::getIns()->level = (eLevel)_stageSelectID; ミスっぽいのでコメントアウトして様子見
				_isFinalized = true;
				SE::getIns()->setPlay(eSE::eSE_selectDetail);
				BGM::getIns()->stopMenuBGM();
			}
			else {
				SE::getIns()->setPlay(eSE::eSE_error);
			}
		}
		else if (Pad::getIns()->get(ePad::bom) == 1) {
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
		GameScenePrm prm((eStage)_stageSelectID, eLevel(_levelSelectID));
		prm._isFromPractice = true;
		_finalizeCounter=0;
		_isFinalized = false;
		for (int i = 0; i < _items.size(); i++) {
			_items[i]->reset( (i==_stageSelectID || i== NUM + _levelSelectID) ? true : false);
		}
		_isActivated = false;
		_implSceneChanged->onSceneChanged(eScene::Game, true, &prm);
		switch (_stageSelectID) {
		case eStage1:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Practice1]++;
			break;
		case eStage2:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Practice2]++;
			break;
		case eStage3:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Practice3]++;
			break;
		case eStage4:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Practice4]++;
			break;
		case eStage5:
			SavedData::getIns()->dat.playedNPerSelect[eSelectType_Practice5]++;
			break;
		}
		return false;
	}
	if (_isCanceled) {
		_cancelCounter++;
	}
	if (_cancelCounter == FINISH_COUNT/2) {
		_isActivated = false;
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
		return false;
	}
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->update();
	}
	return true;
}

void PracticeSelectScene::draw() {
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

void PracticeSelectScene::onResume()
{
	BGM::getIns()->startMenuBGM();
}
