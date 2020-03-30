#include "ShineLineOut.h"
#include <DxLib.h>
#include <math.h>
#include "Define.h"

ShineLineOut::ShineLineOut(float x, float y) : ShineLine(x, y) {
	_x1 = _x2 = x;
	_y1 = _y2 = y;
	_angle = PI * 2 * GetRand(100000) / 100000.f;
	_v = 3.5f + GetRand(250) / 100.f;
	_alfa = 50 + GetRand(155);
	_counter = 0;
	_isEndMove = false;
	_isStartMove = true;
	_color = GetColor(255, 255, 255);
}

bool ShineLineOut::isNear() {
	if ((_x1 - _x2) * (_x1 - _x2) + (_y1 - _y2) * (_y1 - _y2) < 2) {
		return true;
	}
	return false;
}

bool ShineLineOut::update() {
	_counter++;
	if (_isStartMove) {
		_x2 += cos(_angle) * _v;
		_y2 += sin(_angle) * _v;
	}
	if (_counter >= 30) {
		if (GetRand(5) == 0) {
			_isStartMove = false;
		}
		if (GetRand(5) == 0) {
			_isEndMove = true;
		}
		if (isNear()) {
			return false;
		}
	}
	if (_isEndMove) {
		_x1 += cos(_angle) * _v;
		_y1 += sin(_angle) * _v;
	}
	return true;
}
