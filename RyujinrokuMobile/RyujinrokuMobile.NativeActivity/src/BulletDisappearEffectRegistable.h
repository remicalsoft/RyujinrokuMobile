#pragma once
class BulletDisappearEffectRegistable
{
public:
	BulletDisappearEffectRegistable();
	~BulletDisappearEffectRegistable();
	virtual void registBulletDisapperEffect(float x, float y) = 0;
};

