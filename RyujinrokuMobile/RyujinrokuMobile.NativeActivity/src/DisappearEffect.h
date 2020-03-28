#pragma once
#include "Task.h"
#include <DxLib.h>
#include "Utils.h"
#include "Define.h"
#include "Image.h"
#include <list>

class Disappear {
	float _x, _y;
	int _counter;
	int _color;
	float _angle;
public:
	Disappear(float x, float y){
		_x = x;
		_y = y;
		_color = GetRand(4);
		_angle = randf2(PI);
		_counter = 0;
	}
	bool update() {
		_counter++;
		if (_counter > 20) {
			return false;
		}
		return true;
	}
	void draw() {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		if (_counter>10) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - (_counter - 10) * 26);
		}
		DrawRotaGraph(_x, _y, _counter / 6.f, _angle, Image::getIns()->enemyDisappear[_color], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
};

class DisappearEffect : public Task {
	int _counter;
	float _x, _y;
	std::list<Disappear*> _list;
public:
	DisappearEffect(float x, float y) {
		_counter = 0;
		_x = x;
		_y = y;
	}
	~DisappearEffect(){
		for (auto e : _list) {
			delete e;
		}
	}
	bool update() override;
	void draw() override;
};

