#include "BarrageBoss.h"
#include <DxLib.h>
#include "Image.h"

using namespace std;

BarrageBoss::BarrageBoss(Boss *boss, int barrageN, IPlayerInfoGettable* impl, BulletEffectRegistable* implBulletDisappearEffectRegistable) : Barrage(impl, implBulletDisappearEffectRegistable)
{
	_angle = 0;
	_counter = _counter2 = 0;
	_barrageN = barrageN;
	_boss = boss;
	for(int i=0; i<4; i++)
		_launcherImage[i] = Image::getIns()->launcher[i];
	setFunc();
}

BarrageBoss::~BarrageBoss()
{
	for (auto b : _launcher) {
		delete b;
	}
}

bool BarrageBoss::update() 
{
	(this->*_funcList[_barrageN])();
	for (list<Bullet*>::iterator it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			delete (*it);
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	for (vector<Launcher*>::iterator it = _launcher.begin(); it != _launcher.end();) {
		if ((*it)->update() == false) {
			delete (*it);
			it = _launcher.erase(it);
		}
		else {
			it++;
		}
	}
	Barrage::update();
	_counter++;
	return true;
}

void BarrageBoss::draw()
{
	for (auto b : _list) {
		b->draw();
	}
	for (auto l : _launcher) {
		l->draw();
	}
}
