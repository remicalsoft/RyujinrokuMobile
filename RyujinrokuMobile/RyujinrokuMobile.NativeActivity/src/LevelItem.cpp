#include "LevelItem.h"
#include <DxLib.h>
#include "Utils.h"


LevelItem::LevelItem(int x,int y,int img, bool isAvailable) : BaseEffectItem(x,y,img,isAvailable)
{
	_flashCounter = 0;
	_scrollCounter = 0;
}

void LevelItem::reset(bool isAvailable)	//カウンタをリセット
{
	BaseEffectItem::reset(isAvailable);
	_flashCounter = 0;
	_scrollCounter = 0;
}

void LevelItem::skipScroll()
{
	_immutableCounter = 64;
}


bool LevelItem::update(){
	BaseEffectItem::update();

	if (_isFinalized) {
		_flashCounter++;
		if (_flashCounter > 16) {
			_scrollCounter++;
		}
	}
	if (_isCanceled) {
		_cancelCounter++;
		if (_cancelCounter > 16) {
			_scrollCounter++;
		}
	}
	return true;
}

const static int posPrm[] = { -4,4,-3,3,-2,2,-1,1,0 };

void LevelItem::draw(){
	int pos = 0;
	int add = 0;
	int scroll = -(50-Utils::getCosValue_90((_scrollCounter * 16)/256.f, 50));
	if (_isCanceled) {
		scroll *= -1;
	}
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
	if (_isAvailable && _flashCounter / 2 % 2 == 1) {
	}
	else {
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
