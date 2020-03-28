#pragma once

#include "Task.h"
#include "Utils.h"
#include "BulletEffect.h"

class BulletAppearEffect :
	public BulletEffect
{
public:
	BulletAppearEffect(float x, float y);
	bool update() override;
	void draw() override;
};

