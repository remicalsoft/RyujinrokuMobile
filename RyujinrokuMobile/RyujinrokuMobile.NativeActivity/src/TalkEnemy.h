#pragma once

#include "TalkBase.h"
#include <DxLib.h>
#include "Utils.h"
#include "GameData.h"

class TalkEnemy :
	public TalkBase
{
	int _subX, _subY;
public:
	TalkEnemy() {
		_subX = 0;
		_subY = 0;
	}
	void setSub(int subX, int subY) {
		_subX = subX;
		_subY = subY;
	}
	bool update() {
		if (!_isAvailable) {
			_counter++;
			_initX = INIT_X - Utils::getSinValue_90(_counter / 32.f, INIT_X);
			if (_counter > 32) {
				_isAvailable = true;
			}
		}
		if (_isEnabled) {
			_bright += 16;
			if (_bright > 255) {
				_bright = 255;
			}
			_x -= 4;
			if (_x < 0) {
				_x = 0;
			}
		}
		else {
			_bright -= 16;
			if (_bright < 64) {
				_bright = 64;
			}
			_x += 4;
			if (_x > X) {
				_x = X;
			}
		}
		return true;
	}
	void draw() {
		int stage = GameData::getIns()->stage;
		if (!_isAvailable) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * _counter / 32);
		}
		SetDrawBright(_bright, _bright, _bright);
		DrawGraph(360 + _x + _initX + _subX, 150 + _subY, _img, TRUE);
		SetDrawBright(255, 255, 255);
		if (!_isAvailable) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
};

