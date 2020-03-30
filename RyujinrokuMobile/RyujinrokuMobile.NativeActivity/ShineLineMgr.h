#pragma once

#include <list>
#include "ShineLine.h"
#include <memory>

class ShineLineMgr {

public:
	ShineLineMgr();
	virtual ~ShineLineMgr() = default;
	bool update();
	void draw();

private:
	std::list<std::shared_ptr<ShineLine>> _list;
	void regist();

	int _counter;

};
