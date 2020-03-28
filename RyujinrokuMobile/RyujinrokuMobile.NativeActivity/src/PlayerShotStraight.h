#pragma once
#include "PlayerShot.h"
class PlayerShotStraight : public PlayerShot
{
public:
	PlayerShotStraight(float x, float y, float power);
	~PlayerShotStraight();
	bool update() override;
	void draw() override;
};
