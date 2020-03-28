#pragma once
#include "Task.h"
class GrazeEffect :
	public Task
{
	float _x, _y;
	float _v, _ang, _a;
public:
	GrazeEffect(float x, float y);
	~GrazeEffect();
	bool update() override;
	void draw() override;
};

