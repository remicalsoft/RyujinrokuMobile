#pragma once
#include "Task.h"
class MenuItem : public Task
{
	int  _img;
	int  _x, _y;
	int  _counter, _immutableCounter, _flashCounter, _scrollCounter;
	bool _isAvailable;
	bool _isFinalized;
public:
	MenuItem(int n, int img, bool isActivated);
	~MenuItem();
	void finalize() override;
	void enable();
	void disable();
	bool update() override;
	void draw() override;
};

