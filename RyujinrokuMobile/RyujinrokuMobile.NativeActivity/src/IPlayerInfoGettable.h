#pragma once

#include <list>
#include <memory>
#include "PlayerShot.h"

class IPlayerInfoGettable {
public:
	virtual void die() = 0;	//←Gettableと言いながら通知もする良くない例
	virtual void registerGraze() = 0;//←その２
	virtual std::list<std::shared_ptr<PlayerShot>>* getShotList() = 0;
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual float getHitRange() = 0;
	virtual float getGrazeRange() = 0;
	virtual bool isInvincible() = 0;
	virtual bool isBombing() = 0;
	virtual int  getBombPower() = 0;
	virtual float getBombR() = 0;
};
