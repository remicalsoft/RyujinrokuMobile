#include "NameBullet.h"
#include <DxLib.h>


NameBullet::NameBullet(int font, float x, float y, const char* str, int color)
{
	_font = font;
	_str = str;
	_color = color;
	_x = x;
	_y = y;
}

NameBullet::~NameBullet()
{
}

bool NameBullet::update()
{
	_y--;
	if (_y < -60) {
		return false;
	}
	return true;
}

void NameBullet::draw()
{
	DrawStringToHandle(_x, _y, _str, _color, _font);
}
