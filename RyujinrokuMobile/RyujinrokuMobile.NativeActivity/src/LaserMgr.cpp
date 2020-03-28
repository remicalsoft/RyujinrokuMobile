#include "LaserMgr.h"
#include <DxLib.h>
#include "LaserHitCulculator.h"
#include "SE.h"

using namespace std;

LaserMgr::LaserMgr(Player* player)
{
	_player = player;
}


LaserMgr::~LaserMgr()
{
	for (auto l : _list) {
		delete l;
	}
}

void LaserMgr::regist(Laser * laser)
{
	_list.push_back(laser);
}

void LaserMgr::unregistAll()
{
	for (auto l : _list) {
		delete l;
	}
	_list.clear();
}

void LaserMgr::updateHit() 
{
	if (!_player->isInvincible()) {
		if (LaserHitCulculator::itHit(&_list, _player)) {
			_player->die();
		}
	}
}

bool LaserMgr::update()
{
	for (list<Laser*>::iterator it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			delete (*it);
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	updateHit();
	return false;
}

void LaserMgr::draw()
{
	SetDrawMode(DX_DRAWMODE_BILINEAR);//線形補完描画
	for (auto l : _list) {
		l->draw();
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
