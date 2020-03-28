#pragma once

#include <list>
#include "ShineLine.h"

class ShineLineMgr {
	std::list<ShineLine*> _list;
	int _counter;
	int _imgShine;
	void regist();
public:
	ShineLineMgr();
	~ShineLineMgr();
	bool update();
	void draw();
};
