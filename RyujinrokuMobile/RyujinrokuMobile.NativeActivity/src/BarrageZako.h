#pragma once

#include "Barrage.h"
#include <memory>
#include "Enemy.h"
#include "Script.h"

class BarrageZako :
	public Barrage
{
protected :
	std::shared_ptr<Enemy> _enemy;
	Script _script;
	int _counter;

public:
	BarrageZako(std::shared_ptr<Enemy> enemy, Script script, IPlayerInfoGettable* impl, BulletEffectRegistable* implBulletDisappearEffectRegistable);
	~BarrageZako();
	bool update() override;
	void draw() override;
	std::shared_ptr<Enemy> getEnemy() {
		return _enemy;
	}
};

