#include "BarrageZako.h"

using namespace std;

BarrageZako::BarrageZako(std::shared_ptr<Enemy> enemy, Script script, IPlayerInfoGettable *impl, BulletEffectRegistable* implBulletDisappearEffectRegistable) : Barrage(impl, implBulletDisappearEffectRegistable)
{
	_counter = 0;
	_enemy = enemy;
	_script = script;
}


BarrageZako::~BarrageZako()
{
}

bool BarrageZako::update()
{
	Barrage::update();
	if (0 <= _script.barrageType && _script.barrageType < _funcList.size()) {
		(this->*_funcList[_script.barrageType])();
	}
	else {
		printfDx("弾幕タイプの指定が不正です");
	}
	for (list<Bullet*>::iterator it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			delete (*it);
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	if (_list.size() == 0 && !_enemy->_isAlive) {
		return false;
	}
	_counter++;
	return true;
}

void BarrageZako::draw() {
	for (auto b : _list) {
		b->draw();
	}
}
