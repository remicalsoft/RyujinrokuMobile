#include "RunBoss.h"
#include "Define.h"
#include "Utils.h"



RunBoss::RunBoss(Boss* boss)
{
	_boss = boss;
	_x = _boss->getX();
	_y = _boss->getY();
	_counter = 0;
}


RunBoss::~RunBoss()
{
}

bool RunBoss::update()
{
	_counter++;
	_boss->_x = _x - Utils::getSinValue_m90(_counter/(float)TIME,_x);
	_boss->_y = _y - Utils::getSinValue_m90(_counter/(float)TIME,_y-Y);
	if (_counter == TIME) {
		return false;
	}
	return true;
}
