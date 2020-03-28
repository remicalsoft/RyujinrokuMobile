#pragma once

#include "Task.h"
#include "BossDeathParticle.h"
#include <list>

class BossDeathParticleMgr :
	public Task
{
	std::list<BossDeathParticle*> _list;
	int _counter = 0;
	float _x, _y;
public:
	BossDeathParticleMgr();
	~BossDeathParticleMgr();
	bool update() override;
	void draw() override;

	void regist(float x, float y);
};

