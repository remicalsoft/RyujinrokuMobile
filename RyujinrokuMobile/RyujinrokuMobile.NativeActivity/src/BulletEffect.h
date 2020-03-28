#pragma once

#include "Task.h"
#include "Utils.h"

enum eBulletEffectType {
	eBulletEffectType_Appear,
	eBulletEffectType_Disappear,
};

class BulletEffect :
	public Task
{
protected:
	float _x, _y;
	int _counter;
public:
	BulletEffect(float x, float y) {
		_x = x;
		_y = y;
		_counter = 0;
	}
};

