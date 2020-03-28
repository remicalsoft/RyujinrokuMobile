#pragma once

#include <list>
#include "Task.h"

class Fps : public Task {

	std::list<int>	_list;
	int _font;
	float _fps;
	unsigned _counter;

	void		regist();
	unsigned	getWaitTime();

public:
	Fps();
	~Fps();
	bool		update() override;
	void		draw() override;
	void		wait();
	float		get() { return _fps; }
};

