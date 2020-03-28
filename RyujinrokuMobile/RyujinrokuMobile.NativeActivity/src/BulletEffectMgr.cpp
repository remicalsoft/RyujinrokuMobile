#include "BulletEffectMgr.h"
#include "BulletAppearEffect.h"
#include "BulletDisappearEffect.h"

using namespace std;

bool BulletEffectMgr::update(){
	for (list<BulletEffect*>::iterator it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			delete (*it);
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	return false;
}

void BulletEffectMgr::draw(){
	for (auto b : _list) {
		b->draw();
	}
}

void BulletEffectMgr::regist(float x, float y) {
	regist(x,y,eBulletEffectType_Disappear);
}

void BulletEffectMgr::regist(float x, float y, eBulletEffectType type) {
		switch (type) {
	case eBulletEffectType_Appear:
		_list.push_back(new BulletAppearEffect(x, y));
		break;
	case eBulletEffectType_Disappear:
		_list.push_back(new BulletDisappearEffect(x, y));
		break;
	}
}
