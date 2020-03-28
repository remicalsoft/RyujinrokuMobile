#pragma once

#include "Task.h"
#include <DxLib.h>
#include "Define.h"

class SpellCutIn :
	public Task
{
	int _font;
	int _counter;
	float x;
	float y;
	float v;
	float a;
	const char *spellName;
	bool _isAvailable;
public:
	SpellCutIn() {
		_isAvailable = false;
		_font = CreateFontToHandle(FONT, 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	}
	~SpellCutIn() {
		DeleteFontToHandle(_font);
	}
	void initialize(const char* str) {
		spellName = str;
		a = 0;
		x = 280;
		y = 80;
		v = -5;
		_counter = 0;
		_isAvailable = true;
	}
	bool update() override {
		if (!_isAvailable) {
			return false;
		}
		if (_counter<32) {
			a += 8;
		}
		if (_counter == 32) {
			a = 255;
			v = -0.5;
		}
		if (_counter>180) {
			a -= 8;
			if (a < 0) {
				_isAvailable = false;
			}
		}
		x += v;
		_counter++;
		return _isAvailable;
	}
	void draw() override{
		if (!_isAvailable) {
			return;
		}
		if (a != 255) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		}
		DrawStringToHandle(x,y,spellName,GetColor(255,169,169),_font);
		if (a != 255) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
};

