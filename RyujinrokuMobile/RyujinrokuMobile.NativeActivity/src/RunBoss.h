#pragma once

#include "Task.h"
#include "Boss.h"

class Boss;

class RunBoss :
	public Task
{
	Boss *_boss;
	float _x, _y;
	int _counter;
public:
	const static int TIME = 180;
	const static int Y = -300;
	RunBoss(Boss *boss);
	~RunBoss();
	bool update() override;
};

