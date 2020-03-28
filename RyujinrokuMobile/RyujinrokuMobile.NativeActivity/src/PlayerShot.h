#pragma once
#include "Task.h"
enum eShotType{
	eShotTypeStraight,
	eShotTypeTail
};
class PlayerShot : public Task
{
protected:
	int _image;
	float _power;
	float _x, _y, _v, _angle;
	float _range;
	eShotType _type;
public:
	PlayerShot(float x, float y, float power);
	virtual ~PlayerShot();
	virtual bool update() override;
	virtual void draw() override;
	float getX()     { return _x; }
	float getY()     { return _y; }
	float getV()     { return _v; }
	float getAngle() { return _angle; }
	float getRange() { return _range; }
	float getPower() { return _power; }
};

