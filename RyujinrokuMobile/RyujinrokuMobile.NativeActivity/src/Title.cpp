#include "Title.h"
#include <DxLib.h>
#include "Define.h"
#include "GameCounter.h"

char* title[][2] = {
	{ { "ステージ1" },{ "訪れぬ朝の謎を求めて" } },
	{ { "ステージ2" },{ "妖人界のお祭りに紛れて" } },
	{ { "ステージ3" },{ "長い夜を作りし者の正体を求めて" } },
	{ { "ステージ4" },{ "王族の側近への接触を求めて" } },
	{ { "最終ステージ" },{ "龍姫から光を奪還せよ" } },
	{ { "Extraステージ" },{ "龍姫を救出し夜を取り戻せ" } },
	{ { "Phantasmステージ" },{ "暴走せし暴君王女を阻止すべし" } },
};

const int APPEAR_TIME[] = {
	300,//1
	300,//2
	400,//3
	250,//4
	400,//5
	660,//EX
	400,//PH
};

Title::Title(int stage){
	_stage = stage;
	_counter = 0;
	_isAvailable = false;
	_font = CreateFontToHandle(FONT, 50, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

Title::~Title(){
	DeleteFontToHandle(_font);
}

bool Title::update(){
	if (GameCounter::getIns()->get() == APPEAR_TIME[_stage]) {
		_isAvailable = true;
	}
	if (_isAvailable) {
		_counter++;
		if (_counter > 300) {
			_isAvailable = false;
		}
	}
	return true;
}

void Title::draw(){
	if (!_isAvailable) {
		return;
	}
	if (_counter<64) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _counter * 4);
	}
	if (_counter>300 - 120) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (_counter - (300 - 120)) * 2);
	}
	DrawStringToHandle(120, 140, title[_stage][0], GetColor(255, 255, 255), _font);
	DrawStringToHandle( 80, 220, title[_stage][1], GetColor(255, 255, 255), _font);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
