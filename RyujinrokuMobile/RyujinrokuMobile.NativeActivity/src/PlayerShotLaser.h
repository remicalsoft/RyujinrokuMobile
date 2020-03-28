#pragma once

#include "Task.h"
#include <list>
#include "Player.h"
#include <memory>

class Player;

#define PLAYER_LASER_W_ITVL 38
#define PLAYER_LASER_W_SLOW_ITVL 20

class PlayerShotLaser :
	public Task
{
	class Factor {
	public:
		int type;
		float x, y, a;
		Factor(float x, float y, float a) {
			this->x = x;
			this->y = y;
			this->a = a;
			type = GetRand(4);
		}
	};

	std::list<std::shared_ptr<Factor>> _list;
	Player* _player;
public:
	PlayerShotLaser(Player* player);
	~PlayerShotLaser();
	bool update() override;
	void draw() override;
};

