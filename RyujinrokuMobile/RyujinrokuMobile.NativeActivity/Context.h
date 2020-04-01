#pragma once

#include "TouchEvent.h"
#include "Image.h"
#include "Font.h"
#include "ImageBullet.h"

class Context final {

public:
    Context() = delete;
    Context(Image* image, TouchEvent* touchEvent, Font* font, ImageBullet* imageBullet) {
        _image = image;
        _touchEvent = touchEvent;
        _font = font;
        _imageBullet = imageBullet;
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
    ImageBullet* getImageBullet() {
        return _imageBullet;
    }

private:
    Image* _image;
    TouchEvent* _touchEvent;
    Font* _font;
    ImageBullet* _imageBullet;

};
