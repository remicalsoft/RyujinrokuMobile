#include "GameCounter.h"
#include "BossPrm.hpp"

GameCounter::GameCounter() : _n(0)
{
	_isLocked = false;
	_n = 0;
}

GameCounter::~GameCounter()
{
}

void GameCounter::initialize()
{
	_n = 0;
//	_n = APPEAR_TIME[0][0]; // = BossPrm.hpp <- APPEAR_TIME[0][0];
}

void GameCounter::set(int cnt)
{
	_n = cnt;
}

void GameCounter::update() {
	if (!_isLocked) {
		_n++;
	}
	unlock();
}

int GameCounter::get() {
	return _n;
}

void GameCounter::lock()
{
	_isLocked = true;
}

void GameCounter::unlock()
{
	_isLocked = false;
}


