#include "BulletKilledEffectMgr.h"

using namespace std;

BulletKilledEffectMgr::BulletKilledEffectMgr()
{
}

BulletKilledEffectMgr::~BulletKilledEffectMgr()
{
}

void BulletKilledEffectMgr::initialize()
{
	for (list<BulletKilledEffect>::iterator it = _list.begin(); it != _list.end();) {
		it = _list.erase(it);
	}
}

bool BulletKilledEffectMgr::update()
{
	for (list<BulletKilledEffect>::iterator it = _list.begin(); it != _list.end();) {
		if (it->update() == false) {
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	return false;
}

void BulletKilledEffectMgr::draw()
{
	for (auto b : _list) {
		b.draw();
	}
}

void BulletKilledEffectMgr::regist(float x, float y, eBulletColor color)
{
	BulletKilledEffect b(x,y,color);
	_list.push_back(b);
}
