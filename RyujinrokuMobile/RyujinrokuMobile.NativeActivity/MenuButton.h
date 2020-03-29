#pragma once

#include "View.h"
#include "IOnClickListener.h"
#include <string>
#include <memory>

class MenuButton : public View {

public:
    MenuButton(std::shared_ptr<Context> context, int x, int y, std::string str, IOnClickListener* listener) : View(context) {
        _x = x;
        _y = y;
        _isAvailable = true;
        _str = str;
        _listener = listener;
        _endCounter = 0;
        _strDrawWidth = GetDrawStringWidthToHandle(_str.c_str(), _str.length(), _context->getFont()->_font48);
        _strWidth = _strDrawWidth;
    }

    bool update() override;
    void draw() const override;
    bool isPressing(Pos pos) const;
    void setStrDrawWidth(int width) {
        _strDrawWidth = width;
    }

private:
    int _x, _y, _strDrawWidth, _strWidth;
    int _endCounter;
    bool _isAvailable;
    std::string _str;
    IOnClickListener* _listener;

    const static int END_COUNTER_MAX = 24;
};
