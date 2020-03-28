#pragma once

#include "Task.h"
#include "StoreBuyScene.h"

class Board : public Task
{
	int _endCount;
	int _font;
	int _counter;
	int _icons[eEquipItem_Num-1];

public:
	Board();
	~Board();
	bool update() override;
	void draw() override;
	void setEndCount(int endCount) {
		_endCount = endCount;
	}
	void drawIcon();
};

