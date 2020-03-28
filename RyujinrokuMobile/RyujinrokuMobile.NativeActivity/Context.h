#pragma once

#include "TouchEvent.h"
#include "Image.h"
#include "Font.h"

class Context final {

public:
    Context() = delete;
    Context(Image* image, TouchEvent* touchEvent, Font* font) {
        _image = image;
        _touchEvent = touchEvent;
        _font = font;
    }
    Image* getImage() {
        return _image;
    }
    TouchEvent* getTouchEvent() {
        return _touchEvent;
    }
    Font* getFont() {
        return _font;
    }

private:
    Image* _image;
    TouchEvent* _touchEvent;
    Font* _font;

};
