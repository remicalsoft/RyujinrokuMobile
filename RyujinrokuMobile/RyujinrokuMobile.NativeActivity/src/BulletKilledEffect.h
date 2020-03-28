#pragma once

#include "Task.h"
#include "ImageBullet.h"

class BulletKilledEffect :
	public Task
{
	float x, y;
	int _img;
	int _counter;
public:
	BulletKilledEffect(float x, float y, eBulletColor color);
	bool update() override;
	void draw() override;
};

