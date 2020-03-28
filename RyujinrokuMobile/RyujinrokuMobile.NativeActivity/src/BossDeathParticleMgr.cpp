#include "BossDeathParticleMgr.h"

using namespace std;

BossDeathParticleMgr::BossDeathParticleMgr()
{
}


BossDeathParticleMgr::~BossDeathParticleMgr()
{
	for (auto p : _list) {
		delete p;
	}
}

bool BossDeathParticleMgr::update()
{
	if (_counter > 0) {
		_counter++;
	}
	if (0<_counter && _counter<=30) {
		for (int i = 0; i < 20; i++) {
			_list.push_back(new BossDeathParticle(_x, _y));
		}
	}
	for (list<BossDeathParticle*>::iterator it = _list.begin(); it != _list.end();) {
		if (!(*it)->update()) {
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	return true;
}

void BossDeathParticleMgr::draw()
{
	for (auto p : _list) {
		p->draw();
	}
}

void BossDeathParticleMgr::regist(float x, float y)
{
	_counter = 1;
	_x = x;
	_y = y;
}
