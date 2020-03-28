#pragma once
#include "PlayerShot.h"
class PlayerShotTail :
	public PlayerShot
{
public:
	PlayerShotTail(float x, float y, float power);
	~PlayerShotTail();
	bool update() override;
	void draw() override;
};

