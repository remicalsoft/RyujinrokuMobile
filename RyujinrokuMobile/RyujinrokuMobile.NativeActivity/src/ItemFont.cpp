#include "ItemFont.h"
#include <DxLib.h>

using namespace std;

ItemFont::ItemFont(int x, int y, const char * str, int font, int color)
{
	_x = x;
	_y = y;
	_str = new string(str);
	_color = color;
	_isAvailable = false;
	_font = font;
}

ItemFont::~ItemFont()
{
	delete _str;
}

bool ItemFont::update()
{
	return true;
}

void ItemFont::draw()
{
	int x = _x;
	if (_isAvailable) {
		x -= 5;
	}
	else {
		SetDrawBright(100, 100, 100);
	}
	DrawStringToHandle( x, _y, _str->c_str(), _color, _font);
	SetDrawBright(255,255,255);
}
