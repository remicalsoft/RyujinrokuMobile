#include "DisappearEffectMgr.h"

using namespace std;

DisappearEffectMgr::DisappearEffectMgr(){
}

DisappearEffectMgr::~DisappearEffectMgr(){
	for (auto e : _list) {
		delete e;
	}
}

bool DisappearEffectMgr::update(){
	for (list<DisappearEffect*>::iterator it = _list.begin(); it != _list.end();) {
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

void DisappearEffectMgr::draw(){
	for (auto e : _list) {
		e->draw();
	}
}

void DisappearEffectMgr::regist(float x, float y){
	_list.push_back(new DisappearEffect(x, y));
}
