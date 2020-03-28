#pragma once
#include "Task.h"
#include "DisappearEffect.h"
#include <list>

class DisappearEffectMgr : public Task
{
	std::list<DisappearEffect*> _list;
public:
	DisappearEffectMgr();
	~DisappearEffectMgr();
	bool update() override;
	void draw() override;
	void regist(float x, float y);
};

