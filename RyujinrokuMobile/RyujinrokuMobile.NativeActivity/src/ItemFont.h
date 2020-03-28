#pragma once

#include "Task.h"
#include <string>

class ItemFont :
	public Task
{
	int _x, _y;
	std::string* _str;
	int _color;
	bool _isAvailable;
	int _font;
public:
	ItemFont(int x, int y, const char* str, int font, int color);
	~ItemFont();
	bool update() override;
	void draw() override;

	void setColor(int color) {
		_color = color;
	}

	void enable() {
		_isAvailable = true;
	}
	void disable() {
		_isAvailable = false;
	}

};

