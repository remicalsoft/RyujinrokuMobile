#pragma once
#include "Task.h"
class Time :
	public Task
{
	int _img[10];
	int _frame;
public:
	Time();
	~Time();
	bool update() override;
	void draw() override;
	void setTime(int frame);
	int getTime();
	bool isTimeOver();
};

