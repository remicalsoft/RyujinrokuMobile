#include "MenuButton.h"
#include <DxLib.h>

bool MenuButton::update()
{
    return false;
}

void MenuButton::draw() const
{
    int width = GetDrawStringWidthToHandle(_str.c_str(), _str.length(), _context->getFont()->_font30);
    DrawGraph(_x, _y, _context->getImage()->_menuButtonLeft, TRUE);
    DrawModiGraph(
        _x+40,       _y, 
        _x+40+width, _y,
        _x+40+width, _y+95,
        _x+40,       _y+95,
        _context->getImage()->_menuButtonMiddle, TRUE);
    DrawGraph(_x+40+width, _y, _context->getImage()->_menuButtonRight, TRUE);
    DrawFormatStringToHandle(_x + 40, _y + 25, GetColor(255, 255, 255), _context->getFont()->_font30, _str.c_str());
}
