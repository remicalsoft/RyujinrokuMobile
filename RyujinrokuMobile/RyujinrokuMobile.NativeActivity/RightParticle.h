#pragma once

#include "Drawable.h"

class RightParticle : public Drawable {
public:
    RightParticle(std::shared_ptr<Context> context, float dstX, float dstY, int img);
    virtual ~RightParticle() = default;
    bool update() override;
    void draw() const override;
private:
    int _img;
    int _counter;
    float _x, _y, _speed, _angle, _scale;
    float _dstX, _dstY;
};