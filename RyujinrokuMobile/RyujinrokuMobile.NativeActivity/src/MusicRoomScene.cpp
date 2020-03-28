#include "MusicRoomScene.h"
#include "MusicMgr.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "SE.h"
#include "Utils.h"
#include "MenuScenePrm.h"
#include "BgmLoopPosDefine.h"
#include "BGM.h"

#define MUSIC_NUMS eMusicType::eMusicType_Num

music_t musicData[MusicRoomScene::MUSIC_NUM] = {
	{"四聖龍神録2〜Missing Light","dat/bgm/menu/bgm.ogg",19459},
	{"黒い光に弾を撒け","dat/bgm/game/0_0.ogg",1500},
	{"ハピネスダーク","dat/bgm/game/0_1.ogg",2909},
	{"夜間飛行〜Midnight Festival","dat/bgm/game/1_0.ogg",30857},
	{"百華繚乱〜The Beautiful Fireworks","dat/bgm/game/1_1.ogg",0},
	{"幽霊たちの鎮魂歌","dat/bgm/game/2_0.ogg",0},
	{"体操幽霊は開かずの夜の夢を見るか？","dat/bgm/game/2_1.ogg",0},
	{"暗闇の中を往く","dat/bgm/game/3_0.ogg",22685},
	{"スターダスタウェイ","dat/bgm/game/3_1.ogg",3157},
	{"画竜点睛〜Ｒ","dat/bgm/game/4_0.ogg",10971},
	{"光差す龍の紅玉","dat/bgm/game/4_1.ogg",8000},
	{"Decade","dat/bgm/game/4_1S.ogg",0},
	{"凍った夜","dat/bgm/endroll/endroll.ogg",0},
	{"For the most Lunatic Players","dat/bgm/game/5_0.ogg",2857},
	{"時の旅人〜Gulliver","dat/bgm/game/6_0.ogg",0},
	{"運命の塔〜Esperanto","dat/bgm/game/6_1.ogg",0},
	{"星命流転曲〜Darkness","dat/bgm/game/7_0.ogg",0},
};

using namespace std;

MusicRoomScene::MusicRoomScene(ISceneChangedListener * impl, ScenePrmBase * prm) : Scene(impl)
{
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);
	_selectID = 0;
	_playingID = -1;
	_colorSelected = GetColor(255, 255, 255);
	_colorOther = GetColor(50, 50, 50);
	_imgTitle = LoadGraph("dat/image/musicroom/title.png");
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_font = CreateFontToHandle(FONT, 25, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	_fontText = CreateFontToHandle(FONT, 18, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	load();
	_counter = 0;
	MenuScenePrm* p = (MenuScenePrm*)prm;
	_selector = new MusicSelectUtil;
	BGM::getIns()->stopMenuBGM();
}

MusicRoomScene::~MusicRoomScene()
{
	DeleteGraph(_imgTitle);
	DeleteGraph(_imgBack);
	DeleteFontToHandle(_font);
	DeleteFontToHandle(_fontText);
	DeleteSoundMem(_bgm);
	release();
}

void MusicRoomScene::load(bool able) {
	char fname[256];
	sprintf(fname, "dat/txt/musicroom/%02d.txt", able?(_playingID + 1):99);
	int file = FileRead_open(fname);
	char txt[512];
	while (1) {
		if (FileRead_gets(txt, 512, file) == -1) {
			break;
		}
		string* str = new string(txt);
		_txt.push_back(str);
	}
}

void MusicRoomScene::release() {
	for (int i = 0; i < _txt.size(); i++) {
		delete _txt[i];
	}
	_txt.clear();
}

void MusicRoomScene::playSoundRoom(int id) {
	DeleteSoundMem(_bgm);
	_bgm = LoadSoundMem(musicData[id].musicPath);
	SetLoopPosSoundMem(musicData[id].musicLoop, _bgm);
	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP);
}

bool MusicRoomScene::update(){
	_counter++;
	if (Pad::getIns()->get(ePad::bom) == 1) {
		BGM::getIns()->startMenuBGM();
		SE::getIns()->setPlay(eSE::eSE_cancel);
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
		return false;
	}
	if (Pad::getIns()->get(ePad::shot) == 1) {
		_playingID = _selectID;
		if(_selector->canPlayMusic(_playingID))	playSoundRoom(_playingID);
		release();
		load(_selector->canPlayMusic(_playingID));
	}
	if (Utils::isKeyPushed(ePad::down)) {
		//     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + 1) % MUSIC_NUMS;
	}
	if (Utils::isKeyPushed(ePad::up)) {
		//     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + (MUSIC_NUMS - 1)) % MUSIC_NUMS;
	}
	return false;
}

void MusicRoomScene::draw(){

	char drawStr[256];

	DrawGraph(0,0,_imgBack,FALSE);
	DrawGraph((1280-600)/2, 25, _imgTitle, TRUE);

	int color = 0;
	for (int i = 0; i < MUSIC_NUMS; i++) {
		if (i == _selectID) {
			color = _colorSelected;
		}
		else {
			color = _colorOther;
		}
		if(_selector->canPlayMusic(i))	sprintf_s(drawStr, "%02d: %s", i+1, musicData[i].musicName );
		else							sprintf_s(drawStr, "%02d:？？？？？？？？？？？？", i + 1);
		DrawStringToHandle(50, 200 + 40 * i, drawStr, color, _font);
	}
	for (int i = 0; i < _txt.size(); i++) {
		DrawStringToHandle(670, 200 + i * 25, _txt[i]->c_str(), _colorSelected, _fontText);
	}

	if (_counter < 32) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - _counter * 8);
	}
	if (_counter < 32) {
		DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
