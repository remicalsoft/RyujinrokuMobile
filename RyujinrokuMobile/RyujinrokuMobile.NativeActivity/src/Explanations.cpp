#include "Explanations.h"
#include <string.h>
#include <DxLib.h>
#include "Define.h"

const static char* explanation1[] = {
	"ゲームを一度でもプレイ",
	"5章までクリア",
	"5章までクリア",
	"5章までクリア",
	"ゲームを一度でもプレイ",
	"ゲームを一度でもプレイ",
	"ゲームを一度でもプレイ",
	"ゲームを一度でもプレイ",
	"1章をクリア",
	"2章をクリア",
	"3章をクリア",
	"4章をクリア",
	"5章をクリア",
	"6章を一度でもプレイ",
	"6章を一度でもプレイ",
	"6章をクリア",
	"最終章を一度でもプレイ",
	"最終章を一度でもプレイ",
	"最終章をクリア",
};
const static char* explanation2 = "すると見ることができるようになります。";

Explanations::Explanations(int n){
	_n = n;
	_counter1 = 0;
	_counter2 = 0;
	_isFinished1 = false;
	_isFinished2 = false;
	_color = GetColor(255, 255, 255);
	_font = CreateFontToHandle(FONT, 24, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

Explanations::~Explanations(){
	DeleteFontToHandle(_font);
}

bool Explanations::update()
{
	if (!_isFinished1) {
		if (strlen(explanation1[_n]) <= _counter1) {
			_isFinished1 = true;
		}
		else {
			if (explanation1[_n][_counter1] < 0) {
				_counter1++;
			}
			strcpy(_txt1, explanation1[_n]);
			_txt1[_counter1 + 1] = '\0';
		}
		_counter1++;
	}
	if (_isFinished1) {
		strcpy(_txt1, explanation1[_n]);
	}

	if (!_isFinished2) {
		if (_isFinished1) {
			if (strlen(explanation2) <= _counter2) {
				_isFinished2 = true;
			}
			else {
				if (explanation2[_counter2] < 0) {
					_counter2++;
				}
				strcpy(_txt2, explanation2);
				_txt2[_counter2 + 1] = '\0';
			}
			_counter2++;
		}
	}
	if (_isFinished2) {
		strcpy(_txt2, explanation2);
	}
	return false;
}

void Explanations::draw(){
	DrawStringToHandle(650, 780, _txt1, _color, _font);
	if (_isFinished1) {
		DrawStringToHandle(650, 820, _txt2, _color, _font);
	}
}
