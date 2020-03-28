#pragma once

#include "Task.h"
#include "PlayerShot.h"
#include <list>
#include <memory>
#include "IPlayerInfoGettable.h"
#include "ITalkStatusGettable.h"
#include "Bomb.h"
#include "ISpellcardDisablable.h"
#include "Boss.h"
#include "IOnPlayerDiedListener.h"
#include "GrazeEffect.h"
#include "PlayerImageMgr.h"
#include "IShakeListener.h"
#include "PlayerShotLaser.h"

class Bomb;
class Boss;
class PlayerShotLaser;
class PlayerImageMgr;

class Player : public Task, public IPlayerInfoGettable {
	int _imgHitMark;
	float _x, _y;
	int _counter;
	int _dressCounter;
	int _isInvincible;
	int _EndTimeInvincible;
	int _counterInvincible;
	int _showPressingCount;
	void move();
	std::list<std::shared_ptr<PlayerShot>> _shotList;
	ITalkStatusGettable* _implTalkStatusGettable;
	Bomb *_bomb;
	Boss *_boss;
	PlayerImageMgr *_imgMgr;
	float _optionPosX;
	float _optionPosY;
	IOnPlayerDiedListener *_implPlayerDied;
	std::list<std::shared_ptr<GrazeEffect>> _grazeList;
	IShakeListener *_implShake;
	PlayerShotLaser *_playerShotLaser;
	bool _isLaser;
	bool _isLaserNowShooting;
	bool _isFromPractice, _isFromSpellPractice;;

	void doBomb();
	void registerShot();
	void startInvincible(int endtime);

public:
	Player(IOnPlayerDiedListener *impl, IShakeListener *implShake, bool isFromPractice, bool isFromSpellPractice);
	~Player();
	bool update() override;
	void draw() override;
	void reset();
	void setBoss(Boss *boss) {
		_boss = boss;
	}
	void setTalkStatusGettable(ITalkStatusGettable* implTalkStatusGettable);
	void drawHitMark();
	void die() override;
	std::list<std::shared_ptr<PlayerShot>>* getShotList() override;
	float getX() override { return _x; }
	float getY() override { return _y; }
	float getHitRange() override;
	float getGrazeRange() override;
	bool isInvincible() override {
		return _isInvincible;
	}
	bool isBombing() override;
	int getBombPower() override { return 100; }
	float getBombR();
	void finishBomb();
	void registerGraze() override;
	void clearGrazeEffect() {
		_grazeList.clear();
	}
	bool isLaser() {
		return _isLaser;
	}
	bool isLaserNowShooting() {
		return _isLaserNowShooting;
	}
	float getLaserDamageValue();
};
