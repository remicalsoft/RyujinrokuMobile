#include "MenuButton.h"
#include <DxLib.h>

const static int W = 60;
const static int H = 160;

bool MenuButton::update()
{
    if (!_isAvailable) {
        _endCounter++;
    }
    if (_endCounter >= END_COUNTER_MAX) {
        return false;
    }
//    printfDx("ReleasingCount(0)=%d\n", _context->getTouchEvent()->getReleasingCount(0));
    if (_context->getTouchEvent()->getReleasingCount(0) == 1) {
        if (isPressing(_context->getTouchEvent()->getPrePos(0))) {
            _isAvailable = false;
            _listener->onClick(this);
        }
    }
    return true;
}

void MenuButton::draw() const
{
    int left, middle, right;
    if (_isAvailable) {
        if (isPressing(_context->getTouchEvent()->getPos(0))) {
            left = _context->getImage()->_menuButtonLeftPressed;
            middle = _context->getImage()->_menuButtonMiddlePressed;
            right = _context->getImage()->_menuButtonRightPressed;
        }
        else {
            left = _context->getImage()->_menuButtonLeft;
            middle = _context->getImage()->_menuButtonMiddle;
            right = _context->getImage()->_menuButtonRight;
        }
    }
    else {
        if (_endCounter<END_COUNTER_MAX && (_endCounter/4)%2 == 1) {
            left = _context->getImage()->_menuButtonLeftPressed;
            middle = _context->getImage()->_menuButtonMiddlePressed;
            right = _context->getImage()->_menuButtonRightPressed;
        }
        else {
            left = _context->getImage()->_menuButtonLeft;
            middle = _context->getImage()->_menuButtonMiddle;
            right = _context->getImage()->_menuButtonRight;
        }
    }
    DrawGraph(_x, _y, left, TRUE);
    DrawModiGraph(
        _x+W,               _y, 
        _x+W+_strDrawWidth, _y,
        _x+W+_strDrawWidth, _y+H,
        _x+W,               _y+H,
        middle, TRUE);
    DrawGraph(_x+W+_strDrawWidth, _y, right, TRUE);
    int dx = (_strDrawWidth - _strWidth) / 2;
    DrawFormatStringToHandle(_x + W + dx, _y + H / 4 + 5, GetColor(222, 222, 222), _context->getFont()->_font48, _str.c_str());
}

bool MenuButton::isPressing(Pos pos) const
{
    int px = pos.getX();
    int py = pos.getY();
    if (_x <= px && px <= _x + W + _strDrawWidth + W &&
        _y <= py && py <= _y + H) {
        return true;
    }
    return false;
}
