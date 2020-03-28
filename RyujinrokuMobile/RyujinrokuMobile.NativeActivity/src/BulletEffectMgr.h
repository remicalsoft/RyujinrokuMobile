#pragma once
#include "Singleton.h"
#include <list>
#include "BulletEffect.h"

class BulletEffectMgr {

	std::list<BulletEffect*> _list;

public:
	void Initialize() {
		for (auto b : _list) {
			delete b;
		}
		_list.clear();
	}
	bool update();
	void draw();
	void regist(float x, float y);
	void regist(float x, float y, eBulletEffectType type);
};

