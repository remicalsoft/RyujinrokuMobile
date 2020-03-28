#pragma once
#include "Task.h"
class NameBullet :
	public Task
{
	int _font;
	const char *_str;
	float _x, _y;
	int _color;
public:
	NameBullet(int font, float x, float y, const char* str, int color);
	~NameBullet();
	bool update() override;
	void draw() override;
};

