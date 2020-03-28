#include "BulletDisappearEffectMgr.h"

using namespace std;

bool BulletDisappearEffectMgr::update(){
	for (list<BulletDisappearEffect*>::iterator it = _list.begin(); it != _list.end();) {
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

void BulletDisappearEffectMgr::draw(){
	for (auto b : _list) {
		b->draw();
	}
}

void BulletDisappearEffectMgr::regist(float x, float y){
	_list.push_back(new BulletDisappearEffect(x, y));
}
