#include "MenuItem.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"

MenuItem::MenuItem(int n, int img, bool isActivated)
{
	_isFinalized = false;
	_flashCounter = 0;
	_scrollCounter = 0;
	int w, h;
	_img = img;
	GetGraphSize(img, &w, &h);
	_x = 30;
	_y = 45 + (h-4)*n;
	_counter = -1;
	_immutableCounter = 0;
	_isAvailable = false;
	if (isActivated) {
		_isAvailable = true;
	}
}

MenuItem::~MenuItem()
{
}

void MenuItem::finalize(){
	_isFinalized = true;
}

void MenuItem::enable()
{
	_counter = 0;
	_isAvailable = true;
}

void MenuItem::disable()
{
	_counter = -1;
	_isAvailable = false;
}

bool MenuItem::update(){
	if (_counter >= 0) {
		_counter++;
	}
	_immutableCounter++;
	if (_isFinalized) {
		_flashCounter++;
		if (_flashCounter > 16) {
			_scrollCounter++;
		}
	}
	return true;
}

const static int posPrm[] = { -4,4,-3,3,-2,2,-1,1,0 };

void MenuItem::draw(){
	int pos = 0;
	int add = 0;
	int scroll = -(30-Utils::getCosValue_90((_scrollCounter * 16)/256.f, 30));
	if (_counter < 16) {
		pos = posPrm[_counter / 2];
	}
	if (_immutableCounter < 64) {
		add = 50 - Utils::getSinValue_90(_immutableCounter / 60.0f, 50);
	}
	if (!_isAvailable) {
		SetDrawBright(64, 64, 64);
	}
	if (_immutableCounter < 64) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _immutableCounter * 4);
	}
	if (_scrollCounter > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-_scrollCounter * 16);
	}
	if (_isAvailable && _flashCounter/2%2 == 1) {
	} else {
		DrawGraph(_x + pos + add + scroll, _y, _img, TRUE);
	}
	if (_scrollCounter > 0) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (_immutableCounter < 64) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (!_isAvailable) {
		SetDrawBright(255,255,255);
	}
}
