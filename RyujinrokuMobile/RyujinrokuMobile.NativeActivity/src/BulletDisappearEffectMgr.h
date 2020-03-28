#pragma once
#include "Singleton.h"
#include <list>
#include "BulletDisappearEffect.h"

class BulletDisappearEffectMgr : public Singleton<BulletDisappearEffectMgr> {

	std::list<BulletDisappearEffect*> _list;

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
};

