#pragma once

#include <memory>
#include "Enemy.h"
#include "Define.h"

class Enemy;

class BarrageRegistable {
public:
	virtual ~BarrageRegistable() {}
	virtual void regist(eLevel level, std::shared_ptr<Enemy> enemy, Script script) = 0;
};
