#pragma once
#include "Barrage.h"
#include "Launcher.h"
#include "Boss.h"
#include <list>
#include <vector>
#include "Bullet.h"
#include "Laser.h"
#include "BulletEffectRegistable.h"

class BarrageBoss :	public Barrage
{
protected:
	int _launcherImage[4];
	std::vector<Launcher*> _launcher;
	Boss* _boss;
	int _counter2;
	int _barrageN;

public:
	BarrageBoss(Boss*, int barrageN, IPlayerInfoGettable* impl, BulletEffectRegistable* implBulletDisappearEffectRegistable);
	virtual ~BarrageBoss();
	virtual bool update() override;
	virtual void draw() override;
};

