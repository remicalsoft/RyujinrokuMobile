#pragma once

#include "Task.h"
#include "Script.h"
#include "BarrageRegistable.h"

class BarrageRegistable;

class Enemy : public Task
{
	BarrageRegistable* _barrageRegistable;

public:
	Script	_script;
	float	_x, _y;
	float	_v, _angle;
	float   _range;
	float	_hp, _maxHp;
	bool	_isAlive;
	int		_counter;
	int		_imgSizeW, _imgSizeH;
	bool	_isNotAppearedYet;
	std::shared_ptr<Enemy> _this;

	Enemy(Script, BarrageRegistable*);
	~Enemy();
	bool update() override;
	void draw() override;
	void drawHp();

	void setThis(std::shared_ptr<Enemy> enemy) {
		_this = enemy;
	}
	float getX()     { return _x; }
	float getY()     { return _y; }
	float getRange() { return _range; }
	bool  isAppeared() { return !_isNotAppearedYet; }
};
