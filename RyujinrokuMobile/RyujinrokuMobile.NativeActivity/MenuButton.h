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
        _str = str;
        _listener = listener;
    }

    bool update() override;
    void draw() const override;

private:
    int _x, _y;
    std::string _str;
    IOnClickListener* _listener;

};
