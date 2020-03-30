#include "ShineLineIn.h"
#include <DxLib.h>
#include <math.h>
#include "Define.h"

ShineLineIn::ShineLineIn(float x, float y) : ShineLine(x, y) {
	_x1 = _x2 = x;
	_y1 = _y2 = y;
	_angle = atan2(SHINE_Y - y, SHINE_X - x);
	_v = 2.5f + GetRand(250) / 100.f;
	_alfa = GetRand(64);
	_counter = 0;
	_isEndMove = false;
	_isStartMove = false;
	_color = GetColor(255, 255, 255);
}

bool isInShine(float x, float y) {
	if ((SHINE_X - x) * (SHINE_X - x) + (SHINE_Y - y) * (SHINE_Y - y) < SHINE_R * SHINE_R) {
		return true;
	}
	return false;
}

bool ShineLineIn::update() {
	bool isIn2 = false;
	_counter++;
	if (isInShine(_x2, _y2)) {
		isIn2 = true;
	}
	else {
		_x2 += cos(_angle) * _v;
		_y2 += sin(_angle) * _v;
	}
	if (_counter >= 10 || isIn2) {
		if (GetRand(20) == 0 || isIn2) {
			_isEndMove = true;
		}
	}
	if (_isEndMove) {
		if (isInShine(_x1, _y1)) {
			return false;
		}
		else {
			_x1 += cos(_angle) * _v;
			_y1 += sin(_angle) * _v;
		}
	}
	return true;
}
