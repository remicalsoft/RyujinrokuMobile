#include "StorySelectScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Pad.h"
#include "SceneStoryParam.h"
#include "Utils.h"
#include "SE.h"
#include "MenuSelectUtils.h"
#include "Keyboard.h"
#include "SavedData.h"

const static char*itemName[] = {
	"ゲームが始まるまで",
	"世界設定",
	"天体設定[瀧陽系]",
	"種族設定",
	"オープニング(漫画)",
	"主人公[アイシャ]",
	"村長[トランヌ]",
	"1章ボス[妖飛]",
	"2章ボス[濤子]",
	"3章ボス[幽々巳]",
	"4章ボス[妲己]",
	"5章ボス[龍姫]",
	"エンディング(漫画)",
	"6章オープニング(漫画)",
	"6章ボス[全員]",
	"6章エンディング(漫画)",
	"最終章オープニング(漫画)",
	"最終章ボス[龍美]",
	"最終章エンディング(漫画)",
};

enum eItem {
	eTillGameStart,
	eWorld,
	eRoyokei,
	eBreed,
	eOp,
	eAisha,
	eMayor,
	e1,
	e2,
	e3,
	e4,
	e5,
	eEd,
	eExOp,
	eEx,
	eExEd,
	ePhOp,
	ePh,
	ePhEd,
	eNum
};

const static int ITEM_N = sizeof(itemName) / sizeof(char*);

StorySelectScene::StorySelectScene(ISceneChangedListener * impl, ScenePrmBase *prm) : Scene(impl)
{
	_counter = 0;
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_font = CreateFontToHandle(FONT, 32, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_colorSelected = GetColor(255,255,255);
	_colorOther = GetColor(64,64,64);
	_selectID = 0;
	_explanation = new Explanations(0);
    _debugCommandStatus = 0;
}

StorySelectScene::~StorySelectScene()
{
	DeleteGraph(_imgBack);
	DeleteFontToHandle(_font);
	delete _explanation;
}

bool StorySelectScene::update()
{
	_counter++;
    updateDebugCommand();
	if (Utils::isKeyPushed(ePad::down)) {
		_selectID = (_selectID + 1) % ITEM_N;
		delete _explanation;
		_explanation = new Explanations(_selectID);
		SE::getIns()->setPlay(eSE::eSE_upDown);
	}
	if (Utils::isKeyPushed(ePad::up)) {
		_selectID = (_selectID + (ITEM_N - 1)) % ITEM_N;
		delete _explanation;
		_explanation = new Explanations(_selectID);
		SE::getIns()->setPlay(eSE::eSE_upDown);
	}
	if (Pad::getIns()->get(ePad::bom) == 1) {
		SE::getIns()->setPlay(eSE::eSE_cancel);
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
		return false;
	}
	if (Pad::getIns()->get(ePad::shot) == 1) {
		SceneStoryParam* prm = new SceneStoryParam();
		prm->isFromMenu = true;
		bool canDo = false;
		switch (_selectID) {
		case eItem::eTillGameStart:
			if (MenuSelectUtils::havePlayed(eStage1)) {
				_implSceneChanged->onSceneChanged(eScene::StoryPreGame, true, nullptr);
				canDo = true;
			}
			break;
		case eItem::eWorld:
			if (MenuSelectUtils::isClearStage(eStage5)) {
				prm->story = eStory::eStoryWorld;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::eRoyokei:
			if (MenuSelectUtils::isClearStage(eStage5)) {
				prm->story = eStory::eStoryRoyokei;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::eBreed:
			if (MenuSelectUtils::isClearStage(eStage5)) {
				prm->story = eStory::eStoryBreed;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::eOp:
			if (MenuSelectUtils::havePlayed(eStage1)) {
				_implSceneChanged->onSceneChanged(eScene::Op, true, prm);
				canDo = true;
			}
			break;
		case eItem::eMayor:
			if (MenuSelectUtils::havePlayed(eStage1)) {
				prm->story = eStory::eStoryMayor;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::eAisha:
			if (MenuSelectUtils::havePlayed(eStage1)) {
				prm->story = eStory::eStoryAisha;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::e1:
			if (MenuSelectUtils::havePlayed(eStage1)) {
				prm->story = eStory::eStory1;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::e2:
			if (MenuSelectUtils::isClearStage(eStage1)) {
				prm->story = eStory::eStory2;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::e3:
			if (MenuSelectUtils::isClearStage(eStage2)) {
				prm->story = eStory::eStory3;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::e4:
			if (MenuSelectUtils::isClearStage(eStage3)) {
				prm->story = eStory::eStory4;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::e5:
			if (MenuSelectUtils::isClearStage(eStage4)) {
				prm->story = eStory::eStory5;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::eEd:
			if (MenuSelectUtils::isClearStage(eStage5)) {
				_implSceneChanged->onSceneChanged(eScene::Ed, true, prm);
				canDo = true;
			}
			break;
		case eItem::eExOp:
			if (MenuSelectUtils::havePlayed(eStageEX)) {
				_implSceneChanged->onSceneChanged(eScene::ExOp, true, prm);
				canDo = true;
			}
			break;
		case eItem::eEx:
			if (MenuSelectUtils::havePlayed(eStageEX)) {
				prm->story = eStory::eStoryEx;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::eExEd:
			if (MenuSelectUtils::isClearStage(eStageEX)) {
				_implSceneChanged->onSceneChanged(eScene::ExEd, true, prm);
				canDo = true;
			}
			break;
		case eItem::ePhOp:
			if (MenuSelectUtils::havePlayed(eStagePH)) {
				_implSceneChanged->onSceneChanged(eScene::PhOp, true, prm);
				canDo = true;
			}
			break;
		case eItem::ePh:
			if (MenuSelectUtils::havePlayed(eStagePH)) {
				prm->story = eStory::eStoryPh;
				_implSceneChanged->onSceneChanged(eScene::Story, true, prm);
				canDo = true;
			}
			break;
		case eItem::ePhEd:
			if (MenuSelectUtils::isClearStage(eStagePH)) {
				_implSceneChanged->onSceneChanged(eScene::PhEd, true, prm);
				canDo = true;
			}
			break;
		}
		delete prm;
		if (canDo) {
			SE::getIns()->setPlay(eSE::eSE_select);
		}
		else {
			SE::getIns()->setPlay(eSE::eSE_error);
		}
	}
	_explanation->update();
	return false;
}

void StorySelectScene::draw()
{
	bool isBlended = false;
	DrawGraph(0,0,_imgBack, FALSE);
	int color = 0;
	for (int i = 0; i < ITEM_N; i++) {
		if (i == _selectID) {
			color = _colorSelected;
		}
		else {
			color = _colorOther;
		}
		DrawStringToHandle(150, 60+44*i, itemName[i], color, _font);
	}
	_explanation->draw();
	if (_counter < 32) {
		isBlended = true;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - _counter * 8);
	}
	if (isBlended) {
		DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void StorySelectScene::updateDebugCommand()
{
    const static int N = 9;
    //predition
    char key[256];
    GetHitKeyStateAll(key);

    char password[N] = {
        KEY_INPUT_P,
        KEY_INPUT_R,
        KEY_INPUT_E,
        KEY_INPUT_D,
        KEY_INPUT_I,
        KEY_INPUT_T,
        KEY_INPUT_I,
        KEY_INPUT_O,
        KEY_INPUT_N,
    };
    for (int i = 0; i<256; i++) {
        if (i == password[_debugCommandStatus]) {
            continue;
        }
        if (Keyboard::getIns()->getPressingCount(i) == 1) {
            _debugCommandStatus = 0;
            break;
        }
    }
    if (Keyboard::getIns()->getPressingCount(password[_debugCommandStatus]) == 1) {
        _debugCommandStatus++;
        if (_debugCommandStatus == N) {
            PlaySound("dat/sound/menu/bought.wav", DX_PLAYTYPE_BACK);
            _debugCommandStatus = 0;
            SavedData::getIns()->dat.isPremium = (SavedData::getIns()->dat.isPremium == 0) ? 1 : 0;
        }
    }

}
