#include "MenuScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "Utils.h"
#include "SE.h"
#include "MenuScenePrm.h"
#include "BgmLoopPosDefine.h"
#include "BGM.h"
#include "Toast.h"
#include "SavedData.h"
#include "StoreBuyScene.h"
#include <string>
#include "TotalPlayTime.h"

using namespace std;
const static int FINISH_COUNT = 32;

MenuScene::MenuScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl){
	_isFinalized = false;
    _imgPremium = -1;
	_font = CreateFontToHandle(FONT, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_counter = 0;
	_finalizeCounter = 0;
	_selectID = 0;
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Tsubo]) {
		_imgBack = LoadGraph("dat/image/menu/april/back.jpg");
		_imgBackShine = LoadGraph("dat/image/menu/april/backShine.png");
	}
	else {
		_imgBack = LoadGraph("dat/image/menu/back.jpg");
		_imgBackShine = LoadGraph("dat/image/menu/backShine.png");
	}
    if (SavedData::getIns()->dat.isPremium) {
        _imgPremium = LoadGraph("dat/image/menu/premium.png");
    }
	LoadDivGraph("dat/image/menu/menuItem.png", eItem::eNum, 1, eItem::eNum, 264, 40, _imgMenuItem);
	for (int i = 0; i < eItem::eNum; i++) {
		_items.push_back(new MenuItem(i, _imgMenuItem[i], i==_selectID));
		_imgItems.push_back(_imgMenuItem[i]);
	}

	for (int i = 0; i < 1000; i++) {//適当に光をばらつかせる
		_shineLineMgr.update();
	}
	_brightnessBackShine = 0;
	BGM::getIns()->startMenuBGM();
	SavedData::getIns()->markPlayedMusic(eMusicType_Title);
}

MenuScene::~MenuScene(){
	BGM::getIns()->deleteMenuBGM();
	for (int i = 0; i < _items.size(); i++) {
		delete _items[i];
		DeleteGraph(_imgItems[i]);
	}
	for (int i = 0; i < eItem::eNum; i++) {
		DeleteGraph(_imgMenuItem[i]);
	}
	DeleteGraph(_imgBack);
	DeleteGraph(_imgBackShine);
	DeleteFontToHandle(_font);
}

bool MenuScene::update(){
	if (!_isFinalized) {
		if (Utils::isKeyPushed(ePad::down)) {
			_items[_selectID]->disable();
			_selectID = (_selectID + 1) % eNum;
			_items[_selectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Utils::isKeyPushed(ePad::up)) {
			_items[_selectID]->disable();
			_selectID = (_selectID + (eNum - 1)) % eNum;
			_items[_selectID]->enable();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::shot) == 1) {

			if (_selectID == eItem::eReplay || _selectID == eItem::eScore) {
				Toast::getIns()->add("未実装です");
				SE::getIns()->setPlay(eSE::eSE_error);
			}
			else {
				finalizeItems();
				SE::getIns()->setPlay(eSE::eSE_select);
			}
		}
		if (Pad::getIns()->get(ePad::bom) == 1) {
			SE::getIns()->setPlay(eSE::eSE_cancel);
			if (_selectID == eItem::eEnd) {
				finalizeItems();
			}
			else {
				_items[_selectID]->disable();
				_selectID = eItem::eEnd;
				_items[_selectID]->enable();
			}
		}
	}
	_counter++;
	if (_isFinalized) {
		_finalizeCounter++;
	}
	if (_finalizeCounter == FINISH_COUNT) {
		_finalizeCounter = 0;
		_isFinalized = false;
		_counter = 0;
		for (int i = 0; i < eItem::eNum; i++) {
			delete _items[i];
		}
		_items.clear();
		for (int i = 0; i < eItem::eNum; i++) {
			_items.push_back(new MenuItem(i, _imgItems[i], i==_selectID));
		}
		MenuScenePrm* prm = new MenuScenePrm();
		switch (_selectID) {
		case eItem::eGame:		_implSceneChanged->onSceneChanged(eScene::ShoSelect,			true, NULL);	break;
		case eItem::ePractice:	_implSceneChanged->onSceneChanged(eScene::PracticeStageSelect,	true, prm);		break;
		case eItem::eBarrage:	_implSceneChanged->onSceneChanged(eScene::SpellPracticeSelect,	true, prm);		break;
		case eItem::eShop:		_implSceneChanged->onSceneChanged(eScene::Store,				true, NULL);	break;
		case eItem::eReplay:	_implSceneChanged->onSceneChanged(eScene::Replay,				true, NULL);	break;
		case eItem::eStory:		_implSceneChanged->onSceneChanged(eScene::StorySelect,			true, NULL);	break;
		case eItem::eMusic:		_implSceneChanged->onSceneChanged(eScene::Music,				true, prm );	break;
		case eItem::eScore:		_implSceneChanged->onSceneChanged(eScene::End,					true, NULL);	break;
		case eItem::eConfig:	_implSceneChanged->onSceneChanged(eScene::KeyConfig,			true, NULL);	break;
		case eItem::eEnd:		_implSceneChanged->onSceneChanged(eScene::End,					false, NULL);	break;
		default:	ERR("MenuScene::updateにて不明な_selectID"); break;
		}
		delete prm;
		return false;
	}
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->update();
	}
	_shineLineMgr.update();
	return true;
}

void MenuScene::finalizeItems()
{
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->finalize();
	}
	_isFinalized = true;
}

void MenuScene::draw(){
	bool isBlended = false;
	DrawGraph(0,0,_imgBack,FALSE);
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->draw();
	}
	_shineLineMgr.draw();
	
	if (_counter % 3 == 0) {
		_brightnessBackShine = 32 + GetRand(96);
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, _brightnessBackShine);
	DrawGraph(0, 0, _imgBackShine, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	string sversion = Utils::getShortVersionString();
	const char *version = sversion.c_str();
	int w = GetDrawStringWidthToHandle(version, strlen(version), _font);
	DrawFormatStringToHandle(WIN_W-w-25, WIN_H-21, GetColor(255, 255, 255), _font, "v%s", version);
	TotalPlayTime::getIns()->draw(10,WIN_H-50);
    DrawGraph(1280-456,0,_imgPremium,TRUE);

	if (_counter < 32) {
		isBlended = true;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - _counter * 8);
	}
	if (_finalizeCounter > 16) {
		isBlended = true;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (_finalizeCounter - 16) * 16);
	}
	if (isBlended) {
		DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
