#include "BossMover.h"
#include "Define.h"

BossMover::BossMover(Boss* boss, float x, float y, int time)
{
	_boss = boss;
	_preX = boss->getX();
	_preY = boss->getY();
	_movedX = x;
	_movedY = y;
	_time = time;
	_counter = 0;
}

BossMover::~BossMover()
{
}

bool BossMover::update()
{
	if (_counter<=_time) {
		int xlen = _movedX - _preX;
		_boss->_x = _preX + sin(PI / 2 / _time*_counter) * xlen;
		int ylen = _movedY - _preY;
		_boss->_y = _preY + sin(PI / 2 / _time*_counter) * ylen;
		_counter++;
		return true;
	}
	else {
		return false;
	}
}
