#pragma once

#include "BulletEffect.h"

class BulletEffectRegistable
{
public:
	BulletEffectRegistable();
	~BulletEffectRegistable();
	virtual void registBulletEffect(float x, float y) = 0;
	virtual void registBulletEffect(float x, float y, eBulletEffectType type) = 0;
};

