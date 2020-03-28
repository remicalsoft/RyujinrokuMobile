#pragma once

#include "pt_t.h"
#include "Laser.h"
#include "Player.h"
#include <list>

class LaserHitCulculator
{
public:
	LaserHitCulculator();
	~LaserHitCulculator();
	static bool itHit(std::list<Laser*>* list, Player*p);
};

