#pragma once

#include "Task.h"
#include <DxLib.h>
#include "Image.h"
#include "SE.h"

class TheLast :
	public Task
{
	class Obj {
	public:
		float x, y, v;
		Obj(float x, float y, float v) {
			this->x = x;
			this->y = y;
			this->v = v;
		}
	};
	Obj* _obj[2];
	int _a;
	int _counter;
public:
	TheLast() {
		_obj[0] = new Obj(   0, 226, -1);
		_obj[1] = new Obj(-304, 226+140+226, +1);
		_a = 0;
		_counter = 0;
	}
	~TheLast() {
		delete _obj[0];
		delete _obj[1];
	}
	bool update() override {
		_counter++;
		_obj[0]->x += _obj[0]->v;
		_obj[1]->x += _obj[1]->v;
		if (_counter < 32) {
			_a += 8;
		}
		else {
			_a -= 2;
		}
		if (_counter == 32) {
			SE::getIns()->setPlay(eSE::eSE_theLast);
		}
		if (_counter == 32+90) {
			_a = 255;
			SE::getIns()->setPlay(eSE::eSE_theLast);
		}
		if (_counter>90) {
			_a--;
		}
		if (_a < 0) {
			return false;
		}
		return true;
	}
	void draw() override {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _a);
		DrawGraph(_obj[0]->x, _obj[0]->y, Image::getIns()->theLast, TRUE);
		DrawGraph(_obj[1]->x, _obj[1]->y, Image::getIns()->theLast, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
};

