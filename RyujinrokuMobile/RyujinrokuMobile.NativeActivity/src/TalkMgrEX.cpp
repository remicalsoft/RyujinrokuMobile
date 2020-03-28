#include "TalkMgrEX.h"
#include <DxLib.h>
#include "GameCounter.h"
#include "Pad.h"
#include "Define.h"
#include "GameData.h"

#include "TalkDefine.hpp"
#include "BossPrm.hpp"


TalkMgrEX::TalkMgrEX(GameEnding* gameEnding, MusicMgr* musicMgr, Boss* boss) : TalkMgr(gameEnding,musicMgr,boss)
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
		if (i == eKomatta) {
			_aisha.push_back(LoadGraph(fileName));
		} 
		else {
			_aisha.push_back(-1);
		}
				
		sprintf(fileName, "dat/image/talk/%s/%s.png", charaFolderName[1], faceFileName[i]);
		if (i == eDefault || i == eKomatta || i == eIkari) {
			_yohi.push_back(LoadGraph(fileName));
		}
		else {
			_yohi.push_back(-1);
		}
		_talkYohi.setSub(-150, -50);

		sprintf(fileName, "dat/image/talk/%s/%s.png", charaFolderName[2], faceFileName[i]);
		if (i == eDefault || i == eShobon || i == eIkari) {
			_toko.push_back(LoadGraph(fileName));
		}
		else {
			_toko.push_back(-1);
		}
		_talkToko.setSub(-50, -50);

		sprintf(fileName, "dat/image/talk/%s/%s.png", charaFolderName[3], faceFileName[i]);
		if (i == eDefault || i == eMu || i == eIkari) {
			_yuyumi.push_back(LoadGraph(fileName));
		}
		else {
			_yuyumi.push_back(-1);
		}
		_talkYuyumi.setSub(50, -50);

		sprintf(fileName, "dat/image/talk/%s/%s.png", charaFolderName[4], faceFileName[i]);
		if (i == eDefault || i == eAseri || i == eIkari) {
			_dakki.push_back(LoadGraph(fileName));
		}
		else {
			_dakki.push_back(-1);
		}
		_talkDakki.setSub(150, -50);

	}
	_talkAisha.set(_aisha[eKomatta]);
	_talkYohi.set(_enemy[eKomatta]);
	_talkToko.set(_enemy[eShobon]);
	_talkYuyumi.set(_enemy[eShobon]);
	_talkDakki.set(_enemy[eAseri]);
	_imgBackAisha = LoadGraph("dat/image/talk/textBackBlue.png");
	_imgBackEnemy = LoadGraph("dat/image/talk/textBackRed.png");
	_font = CreateFontToHandle(FONT, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_charN = 0;
	_counter = 0;
	set();
}

TalkMgrEX::~TalkMgrEX()
{
	for (auto img : _aisha) {
		DeleteGraph(img);
	}
	for (auto img : _yohi) {
		DeleteGraph(img);
	}
	for (auto img : _toko) {
		DeleteGraph(img);
	}
	for (auto img : _yuyumi) {
		DeleteGraph(img);
	}
	for (auto img : _dakki) {
		DeleteGraph(img);
	}
	DeleteGraph(_imgBackAisha);
	DeleteGraph(_imgBackEnemy);
	DeleteFontToHandle(_font);
}

int TalkMgrEX::getCutInImage() {
	int stage = GameData::getIns()->stage;
	if (stage == eStageEX) {
		if (GameCounter::getIns()->get() >= APPEAR_TIME[stage][2]) {
			switch (_musicMgr->getBossPlayedN()-1) {
			case 0:
				return _yohi.at(0);
				break;
			case 1:
				return _toko.at(0);
				break;
			case 2:
				return _yuyumi.at(0);
				break;
			case 3:
				return _dakki.at(0);
				break;
			}
		}
	}
	return _enemy[0];
}

void TalkMgrEX::enable()
{
	_isAvailable = true;
	set();
}

void TalkMgrEX::set()
{
	if (talk[_stage][_n].chara == eAisha) {
		_talkAisha.set(_aisha[talk[_stage][_n].faceType]);
		disableAll();
		_talkAisha.enable();
	}
	else if (talk[_stage][_n].chara == eYohi) {
		_talkYohi.set(_yohi[talk[_stage][_n].faceType]);
		disableAll();
		_talkYohi.enable();
	}
	else if (talk[_stage][_n].chara == eToko) {
		_talkToko.set(_toko[talk[_stage][_n].faceType]);
		disableAll();
		_talkToko.enable();
	}
	else if (talk[_stage][_n].chara == eYuyumi) {
		_talkYuyumi.set(_yuyumi[talk[_stage][_n].faceType]);
		disableAll();
		_talkYuyumi.enable();
	}
	else if (talk[_stage][_n].chara == eDakki) {
		_talkDakki.set(_dakki[talk[_stage][_n].faceType]);
		disableAll();
		_talkDakki.enable();
	}
}

void TalkMgrEX::disableAll()
{
	_talkAisha.disable();
	_talkYohi.disable();
	_talkToko.disable();
	_talkYuyumi.disable();
	_talkDakki.disable();
}

bool TalkMgrEX::update()
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
			if (talk[_stage][_n + 1].chara == eChara::eEnd) {
				_gameEnding->enable();
				_musicMgr->stop();
			}
			else {
				_charN = 0;
				_counter = 0;
				_n++;
				if (talk[_stage][_n].serif == nullptr) {
					_isAvailable = false;
					if (!_musicMgr->isPlaying()) {
						_musicMgr->play(true);
					}
					GameCounter::getIns()->unlock();
					GameCounter::getIns()->increment();
					disableAll();
					_talkAisha .setIsAvailable(false);
					_talkYohi  .setIsAvailable(false);
					_talkToko  .setIsAvailable(false);
					_talkYuyumi.setIsAvailable(false);
					_talkDakki .setIsAvailable(false);
					_n++;
					_isEnd = true;
					return false;
				}
				set();
			}
		}
		_talkAisha .update();
		_talkYohi  .update();
		_talkToko  .update();
		_talkYuyumi.update();
		_talkDakki .update();
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

void TalkMgrEX::draw()
{
	if (!_isAvailable) {
		return;
	}
	if (_talkAisha.isAppeared()) {
		_talkAisha.draw();
	}
	_talkYohi.draw();
	_talkToko.draw();
	_talkYuyumi.draw();
	_talkDakki.draw();
	if (_talkYohi.isEnabled()) {
		_talkYohi.draw();
	}
	if (_talkToko.isEnabled()) {
		_talkToko.draw();
	}
	if (_talkYuyumi.isEnabled()) {
		_talkYuyumi.draw();
	}
	if (_talkDakki.isEnabled()) {
		_talkDakki.draw();
	}
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
