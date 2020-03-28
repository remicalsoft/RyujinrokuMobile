#pragma once

#include "Player.h"

class Player;

class PlayerImageMgr
{
	int _imgRight[6];
	int _imgLeft[6];
	int _imgUp[4];
	int _imgDown[4];
	int _imgStand[4];

	int _imgRightD[6];
	int _imgLeftD[6];
	int _imgUpD[4];
	int _imgDownD[4];
	int _imgStandD[4];

	int _rightCount;
	int _leftCount;
	int _downCount;
	int _upCount;
	int _count;

	Player* _player;

public:
	PlayerImageMgr(Player* player);
	~PlayerImageMgr();
	void update();
	int getImage();
};

