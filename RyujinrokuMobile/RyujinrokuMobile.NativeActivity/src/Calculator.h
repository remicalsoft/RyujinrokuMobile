#pragma once

#include "Singleton.h"
#include "Player.h"
#include <math.h>
#include "Enemy.h"
#include <list>
#include <memory>
#include "Define.h"
#include "Boss.h"

class Calculator : public Singleton<Calculator> {
	IPlayerInfoGettable *_implPlayerInfoGettable;
	Boss *_boss;
	std::list<std::shared_ptr<Enemy>> *_enemyList;
public:
	Calculator();
	~Calculator();
	void setPlayerInstance(IPlayerInfoGettable* impl) {
		_implPlayerInfoGettable = impl;
	}
	void setBossInstance(Boss* boss) {
		_boss = boss;
	}
	void setEnemyListInstance(std::list<std::shared_ptr<Enemy>> *list) {
		_enemyList = list;
	}
	float getAngleToPlayer(float x, float y) {
		return atan2((double)(_implPlayerInfoGettable->getY() - y), (double)(_implPlayerInfoGettable->getX() - x));
	}
	float getAngleFromBossToPlayer() {
		return atan2((double)(_implPlayerInfoGettable->getY() - _boss->getY()), (double)(_implPlayerInfoGettable->getX() - _boss->getX()));
	}
	float getPlayerX() {
		return _implPlayerInfoGettable->getX();
	}
	float getPlayerY() {
		return _implPlayerInfoGettable->getY();
	}
	Posf getNearestEnemyPos(float x, float y);
};
