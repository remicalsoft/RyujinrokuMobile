#include "BarrageBoss.h"
#include <DxLib.h>
#include "Image.h"

using namespace std;

//BarrageBoss::BarrageBoss(Boss *boss, int barrageN, IPlayerInfoGettable* impl, BulletEffectRegistable* implBulletDisappearEffectRegistable) : Barrage(impl, implBulletDisappearEffectRegistable)
BarrageBoss::BarrageBoss(shared_ptr<Context> context, int barrageN) : Barrage(context)
{
	_barrageN = barrageN;
//	setFunc();
}

BarrageBoss::~BarrageBoss()
{
	//for (auto b : _launcher) {
	//	delete b;
	//}
}

bool BarrageBoss::update() 
{
	(this->*_funcList[_barrageN])();
	for (auto it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	//for (vector<Launcher*>::iterator it = _launcher.begin(); it != _launcher.end();) {
	//	if ((*it)->update() == false) {
	//		delete (*it);
	//		it = _launcher.erase(it);
	//	}
	//	else {
	//		it++;
	//	}
	//}
	Barrage::update();
	_counter++;
	return true;
}

void BarrageBoss::draw() const 
{
	for (auto b : _list) {
		b->draw();
	}
	//for (auto l : _launcher) {
	//	l->draw();
	//}

//	DrawFormatStringToHandle(0, 30, GetColor(255, 0, 0), _context->getFont()->_font100, "%d", _list.size());
}
