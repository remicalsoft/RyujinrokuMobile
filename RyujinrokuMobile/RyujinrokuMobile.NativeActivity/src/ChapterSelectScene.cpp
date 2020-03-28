#include "ChapterSelectScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "SE.h"
#include "Define.h"
#include "ChapterData.h"
#include "GameScenePrm.h"

int ChapterSelectScene::getFadeTime()
{
	return 20;
}

ChapterSelectScene::ChapterSelectScene(ISceneChangedListener* impl, ScenePrmBase* prm) : FadableScene(impl)
{
	GameScenePrm* p = (GameScenePrm*)prm;
	_prm = new GameScenePrm(p->_stage, p->_level);
	_prm->_isFromPractice = p->_isFromPractice;
	_prm->_spellPracticeSpellID = p->_spellPracticeSpellID;

	LoadDivGraph("dat/image/menu/selectChapter.png", 3, 1, 3, 437, 40, _img);

	_itemList.push_back(LevelItem(WIN_W / 2, WIN_H / 2 - 30, _img[1], true));
	_itemList.push_back(LevelItem(WIN_W / 2, WIN_H / 2 + 30, _img[2], false));

	for (auto& item : _itemList) {
		item.skipScroll();
	}

	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_isYes = true;
}

ChapterSelectScene::~ChapterSelectScene()
{
	DeleteGraph(_imgBack);
	for (int i = 0; i < 3; i++) {
		DeleteGraph(_img[i]);
	}
}

bool ChapterSelectScene::update()
{
	if (isAvailable()) {
		for (auto& item : _itemList) {
			item.update();
		}
		if (Pad::getIns()->get(ePad::down) == 1 || Pad::getIns()->get(ePad::up) == 1) {
			_isYes = !_isYes;
			_itemList[_isYes ? 1 : 0].disable();
			_itemList[_isYes ? 0 : 1].enable();
			SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::shot) == 1) {
			if (!_isYes) {
				ChapterData::remove(_prm->_stage, _prm->_level);
			}
			for (int i = 0; i < _itemList.size(); i++) {
				_itemList[i].finalize();
			}
			SE::getIns()->setPlay(eSE::eSE_selectDetail);
			startFadeout();
		}
		if (Pad::getIns()->get(ePad::bom) == 1) {
			SE::getIns()->setPlay(eSE::eSE_cancel);
			_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
			return false;
		}
	}
	if (!FadableScene::update()) {
		if (ChapterData::exists(_prm->_stage, _prm->_level)) {
			ChapterData* data = ChapterData::read(_prm->_stage,_prm->_level);
			_prm->_stage = data->stage;
			_prm->_level = data->level;
			_implSceneChanged->onSceneChanged(eScene::Game, false, _prm);
			delete data;
		}
		else {
			_implSceneChanged->onSceneChanged(eScene::Op, false, _prm);
		}
		return false;
	}
	return true;
}

void ChapterSelectScene::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _brightness);

	int w = 0, h = 0;
	GetGraphSize(_img[0], &w, &h);

	DrawGraph(0,0,_imgBack,FALSE);
	DrawGraph(WIN_W / 2 - w / 2, WIN_H / 2 - 30 - 100, _img[0], TRUE);
	for (auto& item : _itemList) {
		item.draw();
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
