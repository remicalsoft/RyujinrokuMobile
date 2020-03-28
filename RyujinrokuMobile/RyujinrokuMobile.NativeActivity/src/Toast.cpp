#include "Toast.h"
#include "Define.h"
#include <DxLib.h>

using namespace std;

const static int TIME = 180 + 64;

Toast::Toast()
{
	_counter = 0;
	_font = CreateFontToHandle(FONT, 24, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

Toast::~Toast() 
{
	for (auto s : _list) {
		delete s;
	}
	DeleteFontToHandle(_font);
}

void Toast::update()
{
	if (_list.size() == 0) {
		return;
	}
	if (_counter == TIME) {
		delete _list.front();
		_list.pop_front();
		_counter = 0;
	}
	else {
		_counter++;
	}
}

const static int X = 32;
const static int Y = WIN_H-90;
void Toast::draw()
{
	if (_list.size() == 0) {
		return;
	}
	int backA = 169, fontA = 255;
	if (_counter>TIME-64) {
		int t = TIME - _counter;
		backA = backA * t / 64;
		fontA = fontA * t / 64;
	}
	const char* msg = _list.front()->c_str();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, backA);
	DrawBox(X, Y, WIN_W - X, WIN_H - 32, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fontA);
	DrawStringToHandle(X + 32, Y + 17, msg, GetColor(255, 255, 255), _font);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Toast::add(const char * msg)
{
	if (_list.size() > 0) {
		string *str = _list.back();
		if (str->compare(msg)==0) {
			return;
		}
	}
	_list.push_back(new string(msg));
}

void Toast::add(string msg) {
	add(msg.c_str());
}