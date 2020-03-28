#include "MusicMgr.h"
#include <DxLib.h>
#include "Define.h"
#include "BGM.h"

const static int LOOP_POS[eStage_Num] = {
	1500,30857,0,22685,10971,
};
const static int LOOP_POS_BOSS[eStage_Num] = {
	2909,0,0,3157,8000,
};
const static int LOOP_POS_SP = 3000;

const static char *TITLE[] = {
	"♪黒い光に弾を撒け",
	"♪夜間飛行〜Midnight Festival〜",
	"♪幽霊たちの鎮魂祭",
	"♪暗闇の中を往く",
	"♪画龍点睛〜Ｒ〜",
	"♪For the most Lunatic Players",
	"♪時の旅人〜Gulliver",
};
const static char *TITLE_BOSS[] = {
	"♪ハピネスダーク",
	"♪迸る火花の中を征く",
	"♪体操幽霊は開かずの夜の夢を見るか？",
	"♪スターダスタウェイ",
	"♪光差す龍の紅玉",
	"♪EXTRA",
	"♪運命の塔〜Esperanto",
};

const static char *TITLE_SP = "Decade";

MusicMgr::MusicMgr(int stage)
{
	_stage = stage;
	_bgm = -1;
	_bgmSP = -1;
	_counter = 0;
	_isBoss = 0;
	_font = CreateFontToHandle(FONT, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_x = _v = _a = 0;
	_y = OUT_H - 22;
	_title = NULL;
	_bossPlayedN = 0;
	if (stage == eStage5) {
		const char* fileName = "dat/bgm/game/4_1S.ogg";
		_bgmSP = LoadSoundMem(fileName);
		ChangeVolumeSoundMem(BGM::getIns()->getVolume() * 255 / 100, _bgmSP);
		SetLoopPosSoundMem(LOOP_POS_SP, _bgmSP);
	}
}

MusicMgr::~MusicMgr()
{
	DeleteSoundMem(_bgm);
	DeleteSoundMem(_bgmSP);
	DeleteFontToHandle(_font);
}

void MusicMgr::stop()
{
	StopSoundMem(_bgm);
	DeleteSoundMem(_bgm);
	_bgm = -1;
}

bool MusicMgr::isPlaying() {
	return CheckSoundMem(_bgm)==1?true:false;
}

void MusicMgr::setBossPlayedN(int n)
{
	switch (n) {
	case eStage1:
		_bossPlayedN = 0;
		break;
	case eStage2:
		_bossPlayedN = 1;
		break;
	case eStage3:
		_bossPlayedN = 2;
		break;
	case eStage4:
		_bossPlayedN = 3;
		break;
	case eStage5:
		_bossPlayedN = 4;
		break;
	case eStageEX:
		_bossPlayedN = 0;
		break;
	case -1:
		_bossPlayedN = -1;
		break;
	}
}

void MusicMgr::playSP(){
	PlaySoundMem(_bgmSP, DX_PLAYTYPE_LOOP);
	_counter = 0;
	_v = -1;
	_title = TITLE_SP;
	_x = OUT_W - GetDrawStringWidthToHandle(_title, strlen(_title), _font);
}

void MusicMgr::play(bool isBoss)
{
	char fileName[256];
	if (isBoss && _stage == eStageEX) {
		sprintf(fileName, "dat/bgm/game/%d_%d.ogg", _bossPlayedN, 1);
		_bossPlayedN++;
	}
	else {
		sprintf(fileName, "dat/bgm/game/%d_%d.ogg", _stage, isBoss ? 1 : 0);
	}
	_bgm = LoadSoundMem(fileName);
	ChangeVolumeSoundMem(BGM::getIns()->getVolume() * 255 / 100, _bgm);
	SetLoopPosSoundMem(isBoss ? LOOP_POS_BOSS[_stage] : LOOP_POS[_stage], _bgm);
	PlaySoundMem(_bgm,DX_PLAYTYPE_LOOP);
	_counter = 0;
	_v = -1;
	_title = isBoss ? TITLE_BOSS[_stage] : TITLE[_stage];
	_x = OUT_W - GetDrawStringWidthToHandle(_title, strlen(_title), _font);
}

bool MusicMgr::update()
{
	_x += _v;
	if (_counter < 32) {
		_a = 256 * _counter / 32;
	}
	if (_counter==32) {
		_a = 255;
		_v = 0;
	}
	if (_counter>360) {
		_a -= 4;
		if (_a < 0) {
			_a = 0;
		}
	}
	_counter++;
	return false;
}

void MusicMgr::draw()
{
	if (_a != 0 && _title != NULL) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _a);
		DrawStringToHandle(_x, _y, _title, GetColor(255, 255, 255), _font);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
