#pragma once
#include "Task.h"
class EndrollImage :
	public Task
{
	int _img;
	int _counter;
	bool _isEnd;
public:
	EndrollImage(char *, bool isEnd = false);
	~EndrollImage();

	bool update() override;
	void draw() override;
};

