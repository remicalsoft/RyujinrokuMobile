#pragma once
#include "Task.h"
class GameEnding :
	public Task
{
	bool _isAvailable;
	int _bright;
public:
	GameEnding();
	~GameEnding();
	bool update();
	void draw();
	void enable() {
		_isAvailable = true;
	}
};

