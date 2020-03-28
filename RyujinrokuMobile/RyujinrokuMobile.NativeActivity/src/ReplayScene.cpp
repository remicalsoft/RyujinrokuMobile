#include "FadableScene.h"
#include "ReplayScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "Replayer.h"
#include "GameScenePrm.h"
#include "SE.h"
#include "BGM.h"
#include "ChapterData.h"

const static int TIME = 30;
const static int CELL_W = 1251;
const static int CELL_H = 36;
const static int CELL_N = 20;
const static int SEET_N = 1000 / CELL_N;

int ReplayScene::getFadeTime()
{
	return TIME;
}

ReplayScene::ReplayScene(ISceneChangedListener * impl, ScenePrmBase* prm) : FadableScene(impl)
{
	_img = LoadGraph("dat/image/menu/back_dark.jpg");
	_imgCell = LoadGraph("dat/image/menu/replay/cell.png");
	_imgCellSelected = LoadGraph("dat/image/menu/replay/cellSelected.png");
	_imgTitleCell = LoadGraph("dat/image/menu/replay/titleCell.png");
	_counter = 0;
	_seetID = 0;
	_selectID = 0;
	_font = CreateFontToHandle(FONT, 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_selectID = 0;
	initializeCell();
}

ReplayScene::~ReplayScene()
{
	DeleteGraph(_img);
	DeleteGraph(_imgCell);
	DeleteGraph(_imgCellSelected);
	DeleteGraph(_imgTitleCell);
	DeleteFontToHandle(_font);
	for (auto a : _list) {
		delete a;
	}
}

void ReplayScene::initializeCell()
{
	for (auto a : _list) {
		delete a;
	}
	_list.clear();
	int x = (WIN_W - CELL_W) / 2;
	int y = (WIN_H - CELL_H*(CELL_N + 1)) / 2;
	for (int i = 0; i < CELL_N; i++) {
		_list.push_back(new ReplayCell(x, y + CELL_H*(i+1), i+CELL_N*_seetID, _imgCell, _imgCellSelected, _font));
	}
	_list[_selectID]->enable();

}

void ReplayScene::updateCell()
{
	for (auto a : _list) {
		a->disable();
	}
	_list.at(_selectID)->enable();
}

bool ReplayScene::update()
{
	BGM::getIns()->startMenuBGM();
	_counter++;
	if (isAvailable()) {
		if (Pad::getIns()->get(ePad::bom) == 1) {
			_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
		}
		else if (Pad::getIns()->get(ePad::shot) == 1) {
			if (_list.at(_selectID)->isAvailable()) {
				startFadeout();
				SE::getIns()->setPlay(eSE::eSE_select);
			}
			else {
				SE::getIns()->setPlay(eSE::eSE_error);
			}
		}
		if (Pad::getIns()->get(ePad::down) == 1 || Pad::getIns()->get(ePad::down) > 30 && ((Pad::getIns()->get(ePad::down) % 2) == 0)) {
			_selectID++;
			if (_selectID == CELL_N) {
				_seetID++;
				if (_seetID == SEET_N) {
					_seetID = 0;
				}
				_selectID = 0;
				initializeCell();
			}
			else {
				updateCell();
			}
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::up) == 1 || Pad::getIns()->get(ePad::up) > 30 && ((Pad::getIns()->get(ePad::up) % 2) == 0)) {
			_selectID--;
			if (_selectID < 0) {
				_seetID--;
				if (_seetID < 0) {
					_seetID = SEET_N - 1;
				}
				_selectID = CELL_N - 1;
				initializeCell();
			}
			else {
				updateCell();
			}
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::right) == 1 || Pad::getIns()->get(ePad::right) > 30 && ((Pad::getIns()->get(ePad::right) % 4) == 0)) {
			_seetID++;
			if (_seetID == SEET_N) {
				_seetID = 0;
			}
			_selectID = 0;
			initializeCell();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		if (Pad::getIns()->get(ePad::left) == 1 || Pad::getIns()->get(ePad::left) > 30 && ((Pad::getIns()->get(ePad::left) % 4) == 0)) {
			_seetID--;
			if (_seetID < 0) {
				_seetID = SEET_N - 1;
			}
			_selectID = 0;
			initializeCell();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
	}
	if (!FadableScene::update()) {
		ChapterData::removeReplay();
		ReplayHeader *h = _list.at(_selectID)->getReplayHeader();
		Replayer::getIns()->startReplay(_list.at(_selectID)->getFileName());
		GameScenePrm prm((eStage)h->stage, (eLevel)h->level);
		_implSceneChanged->onSceneChanged(eScene::Game, true, &prm);
		BGM::getIns()->stopMenuBGM();

		FadableScene::startFadein();
		return false;
	}
	return true;
}

void ReplayScene::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _brightness);
	DrawGraph(0, 0, _img, TRUE);
	int y = (WIN_H - CELL_H*(CELL_N + 1)) / 2;
	DrawGraph((WIN_W-CELL_W)/2, y, _imgTitleCell, TRUE);
	for (auto a : _list) {
		a->draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

