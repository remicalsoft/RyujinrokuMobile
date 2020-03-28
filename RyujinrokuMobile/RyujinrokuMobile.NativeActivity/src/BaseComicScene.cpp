#include "BaseComicScene.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include "SceneStoryParam.h"
#include "GameScenePrm.h"
#include "SE.h"

using namespace std;

const static int CEN = W / 2;
const static int SPD = 40;

BaseComicScene::BaseComicScene(ISceneChangedListener* impl, ScenePrmBase* prm) : Scene(impl), _coma(0), _page(0), _counter(0), _totalComa(0){
	_isFromMenu = false;
	_gotoEndroll = false;
	_stage = eStage1;
	_level = eLevel_Easy;
	SceneStoryParam*p = dynamic_cast<SceneStoryParam*>(prm);
	if (p != NULL) {
		_isFromMenu = p->isFromMenu;
		_gotoEndroll = p->gotoEndroll;
	}
	else {
		_isFromMenu = false;
		GameScenePrm *pp = dynamic_cast<GameScenePrm*>(prm);
		if (pp != nullptr) {
			_stage = pp->_stage;
			_level = pp->_level;
		}
	}
	_font = CreateFontToHandle(FONT, 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_color = GetColor(255, 255, 255);
}

BaseComicScene::~BaseComicScene()
{
	DeleteFontToHandle(_font);
}

bool BaseComicScene::initialize() {
	setPrm();
    setVoiceFilePathPrefix();

	_posList = _list[_page];
	_pos = _posList[_coma];
	_prePos = Pos::createInitPos();
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");

	return true;
}

void BaseComicScene::finalize() {
	DeleteGraph(_image);
	DeleteGraph(_imgBack);
	for (auto p : _fileList) {
		delete p;
	}
}

bool BaseComicScene::update()
{
	_counter++;
    if (_counter == SPD) {
        playVoice();
    }
	if (Pad::getIns()->get(ePad::shot) == 1) {
        _coma++;
        _totalComa++;
		_counter = 0;
		if (_posList.size() <= _coma) {
			_coma = 0;
			_page++;
			if (_list.size() <= _page) {
				goNextScene();
				return false;
			}
			else {
				DeleteGraph(_image);
				_image = LoadGraph(_fileList[_page]);
				_posList = _list[_page];
				SE::getIns()->setPlay(eSE::eSE_page);
			}
			_prePos = Pos::createInitPos();
		}
		else {
			_prePos = _pos;
		}
		_pos = _posList[_coma];
	}
	if (Pad::getIns()->get(ePad::bom) == 1) {
		SE::getIns()->setPlay(eSE::eSE_cancel);
		_coma--;
		_counter = SPD;
		if (_coma < 0) {
			_page--;
			if (_page < 0) {
				_page = 0;
				_coma = 0;
			}
			else {
				DeleteGraph(_image);
				_image = LoadGraph(_fileList[_page]);
				_posList = _list[_page];
				_coma = _list[_page].size() - 1;
			}
		}
        if (_totalComa > 0) {
            _totalComa--;
        }
        _pos = _posList[_coma];
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		goNextScene();
		return false;
	}
	return true;
}

void BaseComicScene::goNextScene() {
	finalize();
	if (_isFromMenu) {
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
	}
	else if (_gotoEndroll) {
		_implSceneChanged->onSceneChanged(eScene::Endroll, true, NULL);
	}
	else {
		if (_stage == eStagePH) {
			_implSceneChanged->onSceneChanged(eScene::ToBeContinued, false, nullptr);
		}
		else {
			GameScenePrm prm(_stage, _level);
			_implSceneChanged->onSceneChanged(eScene::Game, false, &prm);
		}
	}
}

void BaseComicScene::readFileName(char * mjName){
	int n = 0;
	for (auto p : _list) {
		char* fileName = new char[256];
		sprintf(fileName, "dat/image/comic/%s/%02d.jpg", mjName, n);
		_fileList.push_back(fileName);
		n++;
	}
	_image = LoadGraph(_fileList[0]);
}

void BaseComicScene::draw(){
	DrawGraph(0,0,_imgBack,FALSE);

	SetDrawMode(DX_DRAWMODE_BILINEAR);
	float x, y;
	float nowX = (WIN_W / 2) - _pos.x*(W / 2)*_pos.scale;
	float nowY = (WIN_H / 2) - _pos.y*(H / 2)*_pos.scale;
	float preX = (WIN_W / 2) - _prePos.x*(W / 2)*_prePos.scale;
	float preY = (WIN_H / 2) - _prePos.y*(H / 2)*_prePos.scale;
	float scale = 0;
	if (_counter < SPD) {
		x = preX + Utils::getSinValue_90(_counter / (float)SPD, nowX - preX);
		y = preY + Utils::getSinValue_90(_counter / (float)SPD, nowY - preY);
		scale = _prePos.scale + Utils::getSinValue_90(_counter / (float)SPD, _pos.scale - _prePos.scale);
	}
	else {
		x = nowX;
		y = nowY;
		scale = _pos.scale;
	}
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawRotaGraphF(x, y, scale, 0, _image, TRUE);
	SetDrawMode(DX_DRAWMODE_NEAREST);
	DrawStringToHandle(5, WIN_H - 18, "ショットキー:進む　ボムキー:戻る　スタートキー(Esc):スキップ", _color, _font);
}

void BaseComicScene::playVoice() {
    char path[1024];
    sprintf(path, "%s%03d.wav", _voiceFilePathPrefix.c_str(), _totalComa);
    StopSoundFile();
    PlaySoundFile(path, DX_PLAYTYPE_BACK);
}