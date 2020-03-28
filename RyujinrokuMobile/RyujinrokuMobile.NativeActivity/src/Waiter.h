#pragma once
#include "Task.h"
class Waiter :
	public Task
{
	int _time;
	int _counter;
public:
	Waiter(int time) {
		_counter = 0;
		_time = time;
	}
	~Waiter();
	bool update() {
		_counter++;
		if (_time == _counter) {
			return false;
		}
		return true;
	}
};

