#pragma once

#include "Task.h"
#include <vector>
#include <vector>
#include "Image.h"
#include <DxLib.h>
#include "Define.h"
#include "PlayerLaserFactor.h"

class PlayerLaser {
	int _counter;
	std::vector<PlayerLaserFactor*> _line;
	std::vector<std::vector<PlayerLaserFactor*>> _list;
	float _r;
	float _a;
public:
	PlayerLaser();
	~PlayerLaser();
	void update();
	void draw(float x, float y);
	float getR() { return _r; }
};

