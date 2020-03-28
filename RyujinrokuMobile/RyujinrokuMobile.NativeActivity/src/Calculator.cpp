#include "Calculator.h"
#include "Utils.h"
#include "BossPrm.hpp"

using namespace std;

Calculator::Calculator()
{
	_enemyList = nullptr;
	_implPlayerInfoGettable = nullptr;
}


Calculator::~Calculator()
{
}

Posf Calculator::getNearestEnemyPos(float x, float y)
{
	Posf pos(-1.f, -1.f);
	if (_enemyList->size()==0 && !_boss->isBrrageAlive()) {
		return pos;
	}
	if (_boss->getHpMax() == INF_HP) {
		return pos;
	}
	if (_boss->isAvailable() && _boss->isBrrageAlive()) {
		if (_boss->isInvinsible()) {
			return pos;
		}
		pos.x = _boss->_x;
		pos.y = _boss->_y;
		return pos;
	}
	bool isFirst = true;
	float minLen = 0, len = 0;
	shared_ptr<Enemy> enemy = nullptr;
	for (list<shared_ptr<Enemy>>::iterator it = _enemyList->begin(); it != _enemyList->end();) {
		len = Utils::getLength(x, y, (*it)->getX(), (*it)->getY());
		if (isFirst) {
			minLen = len;
			enemy = *it;
			isFirst = false;
		}
		else {
			if (minLen > len) {
				minLen = len;
				enemy = *it;
			}
		}
		it++;
	}
	pos.x = enemy->getX();
	pos.y = enemy->getY();
	return pos;
}
