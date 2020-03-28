#pragma once

#include "Task.h"

class BossDeathParticle :
	public Task
{
	int _counter;
	float _x, _y, _v, _a, _ang;
public:
	BossDeathParticle(float x, float y);
	~BossDeathParticle();
	bool update() override;
	void draw() override;
};

