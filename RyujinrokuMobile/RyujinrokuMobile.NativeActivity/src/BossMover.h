#pragma once
#include "Task.h"
#include "Boss.h"

class Boss;

class BossMover :
	public Task
{
	Boss* _boss;
	float _preX, _preY;
	float _movedX, _movedY;
	int _time, _counter;

public:
	BossMover(Boss*, float x, float y, int time);
	~BossMover();
	bool update() override;
};

