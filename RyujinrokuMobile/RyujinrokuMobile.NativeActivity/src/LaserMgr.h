#pragma once

#include "Task.h"
#include "Laser.h"
#include "pt_t.h"
#include "Player.h"
#include <list>

class Player;

class LaserMgr :
	public Task
{
	Player* _player;
	std::list<Laser*> _list;
public:
	LaserMgr(Player* player);
	~LaserMgr();
	void regist(Laser* laser);
	void unregistAll();
	void updateHit();
	bool update() override;
	void draw() override;
	std::list<Laser*>* getList() {
		return &_list;
	}
};

