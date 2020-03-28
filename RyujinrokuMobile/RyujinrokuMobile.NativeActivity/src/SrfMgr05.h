#pragma once

#include "DxLib.h"
#include <list>

#include "Srf.h"

class SrfMgr05{
	std::list<Srf*> _list;
	int _handle[eSRF00_DATANUM];

#define START_N (-1)
#define END_N   (+7)

public:
	SrfMgr05();
	~SrfMgr05();
	bool update();
	void draw(VECTOR offset);
};
