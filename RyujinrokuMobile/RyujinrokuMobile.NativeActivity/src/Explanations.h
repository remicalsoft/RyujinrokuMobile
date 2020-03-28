#pragma once
#include "Task.h"
class Explanations :
	public Task
{
	int _n;
	int _font;
	int _color;
	int _counter1, _counter2;
	bool _isFinished1, _isFinished2;
	char _txt1[256], _txt2[256];
public:
	Explanations(int n);
	~Explanations();
	bool update() override;
	void draw() override;
};

