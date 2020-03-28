#pragma once

#include "Task.h"
#include "Utils.h"
#include "BulletEffect.h"

class BulletDisappearEffect :
	public BulletEffect
{
public:
	BulletDisappearEffect(float x, float y) : BulletEffect(x,y) {
		_x = x + randf2(20);
		_y = y + randf2(20)+20;
	}
	bool update()override;
	void draw() override;
};

