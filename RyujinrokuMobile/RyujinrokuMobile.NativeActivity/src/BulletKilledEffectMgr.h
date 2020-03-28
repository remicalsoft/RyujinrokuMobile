#pragma once

#include "BulletKilledEffect.h"
#include <list>
#include "ImageBullet.h"
#include "Singleton.h"

class BulletKilledEffectMgr :
	public Singleton<BulletKilledEffectMgr>
{
	std::list<BulletKilledEffect> _list;
public:
	BulletKilledEffectMgr();
	~BulletKilledEffectMgr();
	void initialize();
	bool update();
	void draw();
	void regist(float x, float y, eBulletColor color);
};

