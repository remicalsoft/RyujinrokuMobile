#pragma once
#include "Task.h"
#include "Script.h"
#include <vector>
#include <list>
#include "Enemy.h"
#include <memory>
#include "BarrageRegistable.h"
#include "Barrage.h"
#include "Player.h"
#include "DisappearEffectMgr.h"
#include "ItemRegistable.h"
#include "BulletEffectRegistable.h"
#include "EnemyAppearMgr.h"

class EnemyMgr : public Task {
	std::vector<Script>* _scriptList;
	std::list<std::shared_ptr<Enemy>> _enemyList;
	BarrageRegistable *_barrageResistable;
	Player* _player;
	DisappearEffectMgr _disappearEffectMgr;
	ItemRegistable* _implItemRegistable;
	BulletEffectRegistable* _implBulletEffectRegistable;
	EnemyAppearMgr _enemyAppearMgr;

	void calcIsHit();

public:
	EnemyMgr(BarrageRegistable*, Player *p, ItemRegistable* impl, BulletEffectRegistable* implB);
	~EnemyMgr();
	bool initialize() override;
	void finalize() override;
	bool update() override;
	void draw() override;
	void drawHp();
	void kill();
};

