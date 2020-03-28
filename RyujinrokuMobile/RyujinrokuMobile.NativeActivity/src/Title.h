#pragma once
#include "Task.h"
class Title : public Task
{
	int _stage;
	int _counter;
	int _font;
	bool _isAvailable;
public:
	Title(int stage);
	~Title();
	bool update() override;
	void draw() override;
};
