#include "TalkMgr.h"
#include <DxLib.h>
#include "GameCounter.h"
#include "Pad.h"
#include "Define.h"
#include "GameData.h"

#include "TalkDefine.hpp"

TalkMgr::TalkMgr(GameEnding* gameEnding, MusicMgr* musicMgr, Boss* boss)
{
	_gameEnding = gameEnding;
	_musicMgr = musicMgr;
	_boss = boss;
	_stage = GameData::getIns()->stage;
	_isEnd = false;
	_n = 0;
	_isAvailable = false;
	for (int i = 0; i < eFaceNum; i++) {
		char fileName[128];
		sprintf(fileName, "dat/image/talk/%s/%s.png", charaFolderName[0], faceFileName[i]);
		_aisha.push_back(LoadGraph(fileName));
		sprintf(fileName, "dat/image/talk/%s/%s.png", charaFolderName[_stage+1], faceFileName[i]);
		_enemy.push_back(LoadGraph(fileName));
	}
	_talkAisha.set(_aisha[0]);
	_talkEnemy.set(_enemy[0]);
	_imgBackAisha = LoadGraph("dat/image/talk/textBackBlue.png");
	_imgBackEnemy = LoadGraph("dat/image/talk/textBackRed.png");
	_font = CreateFontToHandle(FONT, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_charN = 0;
	_counter = 0;
	set();
}

TalkMgr::~TalkMgr()
{
	for (auto img : _aisha) {
		DeleteGraph(img);
	}
	for (auto img : _enemy) {
		DeleteGraph(img);
	}
	DeleteGraph(_imgBackAisha);
	DeleteGraph(_imgBackEnemy);
	DeleteFontToHandle(_font);
}

int TalkMgr::getCutInImage() {
	return _enemy[0];
}

void TalkMgr::set()
{
	if (talk[_stage][_n].chara == eAisha) {
		_talkAisha.set(_aisha[talk[_stage][_n].faceType]);
		_talkAisha.enable();
		_talkEnemy.disable();
	}
	else {
		_talkEnemy.set(_enemy[talk[_stage][_n].faceType]);
		_talkAisha.disable();
		_talkEnemy.enable();
	}
}

bool TalkMgr::update()
{
	if (!_isAvailable) {
		if (GameCounter::getIns()->get() == _boss->getStartTalkCount()) {
			_musicMgr->stop();
			_isAvailable = true;
			set();
		}
	}
	if(_isAvailable) {
		GameCounter::getIns()->lock();
		if (Pad::getIns()->get(ePad::shot) == 1 || Pad::getIns()->get(ePad::change)>0) {
			if (_isEnd && talk[_stage][_n + 1].serif == nullptr) {
				_gameEnding->enable();
				_musicMgr->stop();
			}
			else {
				_charN = 0;
				_counter = 0;
				_n++;
				if (talk[_stage][_n].serif == nullptr) {
					_isAvailable = false;
					_musicMgr->play(true);
					GameCounter::getIns()->unlock();
					GameCounter::getIns()->increment();
					_talkAisha.setIsAvailable(false);
					_talkEnemy.setIsAvailable(false);
					_n++;
					_isEnd = true;
					return false;
				}
				set();
			}
		}
		_talkAisha.update();
		_talkEnemy.update();
		_counter++;
		if (strlen(talk[_stage][_n].serif) > _charN) {
			_charN++;
			if (talk[_stage][_n].serif[_charN] < 0) {
				_charN++;
			}
		}
	}
	return false;
}

void TalkMgr::draw()
{
	if (!_isAvailable) {
		return;
	}
	_talkAisha.draw();
	_talkEnemy.draw();
	if (_talkAisha.isEnabled()) {
		DrawGraph(62, 800, _imgBackAisha, TRUE);
	}
	else {
		DrawGraph(62, 800, _imgBackEnemy, TRUE);
	}
	int sub = 0;
	char name[256];
	char txt[256];
	strcpy(txt, talk[_stage][_n].serif);
	txt[_charN] = '\0';
	if (_counter < 16) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _counter * 16);
		sub = -16 + _counter;
	}
	DrawStringToHandle(90, 825+sub, charaName[talk[_stage][_n].chara], GetColor(255, 255, 255), _font);
	DrawStringToHandle(75, 865+sub, txt, GetColor(255, 255, 255), _font);
	if (_counter < 16) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void TalkMgr::enable() {
	_isAvailable = true;
	set();
}

void TalkMgr::skip()
{
	while (1) {
		if (talk[_stage][_n].serif == nullptr) {
			_isAvailable = false;
//			_musicMgr->play(true);
			GameCounter::getIns()->unlock();
			GameCounter::getIns()->increment();
			_talkAisha.setIsAvailable(false);
			_talkEnemy.setIsAvailable(false);
			_n++;
			_isEnd = true;
			return;
		}
		_n++;
	}
}
