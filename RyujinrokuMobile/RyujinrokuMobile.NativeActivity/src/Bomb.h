#pragma once

#include "Player.h"
#include "Task.h"
#include "PlayerLaser.h"

class Player;

class Bomb :
	public Task
{
	float _a;
	int _counter;
	int _endCounter;
	PlayerLaser _laser;
	Player* _player;

public:
	Bomb(Player* player);
	bool update() override;
	void draw() override;
	float getBombR();
	void finish();
};
