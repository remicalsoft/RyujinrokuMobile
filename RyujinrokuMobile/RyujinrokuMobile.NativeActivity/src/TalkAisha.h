#pragma once

#include "TalkBase.h"
#include <DxLib.h>
#include "Utils.h"

class TalkAisha :
	public TalkBase
{
public:
	bool update() {
		if (!_isAvailable) {
			_counter++;
			_initX = -INIT_X + Utils::getSinValue_90(_counter/32.f, INIT_X);
			if (_counter > 32) {
				_isAvailable = true;
			}
		}
		if (_isEnabled) {
			_bright += 16;
			if (_bright > 255) {
				_bright = 255;
			}
			_x += 4;
			if (_x > X) {
				_x = X;
			}
		}
		else {
			_bright -= 16;
			if (_bright < 64) {
				_bright = 64;
			}
			_x -= 4;
			if (_x < 0) {
				_x = 0;
			}
		}
		return true;
	}
	void draw() {
		if (!_isAvailable) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * _counter / 32);
		}
		SetDrawBright(_bright, _bright, _bright);
		DrawGraph(-50+_x+_initX, 150, _img, TRUE);
		SetDrawBright(255,255,255);
		if (!_isAvailable) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
};

