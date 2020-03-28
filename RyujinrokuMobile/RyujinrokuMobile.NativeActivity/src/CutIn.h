#pragma once

#include "Task.h"
#include <DxLib.h>
#include "Image.h"
#include "SE.h"

class CutIn :
	public Task
{
	float _x, _y;
	float _v;
	float _a;
	int _counter;
	int _img;
public:
	CutIn(int img) {
		_x = 700;
		_y = 200;
		_v = 10;
		_counter = 0;
		_a = 0;
		_img = img;
		SE::getIns()->setPlay(eSE::eSE_spell);
	}
	~CutIn() {}
	bool update() override {
		if (_counter > 152) {
			return false;
		}
		if (_counter<32) {
			_a += 8;
		}
		if (_counter == 40) {
			_v = 2;
		}
		if (_counter > 120) {
			_a -= 8;
		}
		_x -= _v;
		_counter++;
		return true;
	}
	void draw() override {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _a);
		DrawGraphF(_x,_y,_img,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
};

