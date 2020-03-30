#include "RightParticle.h"
#include <DxLib.h>
#include "MathUtils.h"
#include <math.h>
#include "Define.h"
#include "MathUtils.h"

RightParticle::RightParticle(std::shared_ptr<Context> context, float dstX, float dstY, int img) : Drawable(context)
{
    float randAngle = randf2(PI);
    _x = dstX + cos(randAngle) * (120 + randf2(110));
    _y = dstY + sin(randAngle) * (120 + randf2(110));
    _dstX = dstX;
    _dstY = dstY;
    _angle = MathUtils::getAngle(_x, _y, _dstX, _dstY);
    _speed = 4 + randf2(2);
    _scale = 0.5 + randf(0.5);
    _counter = 0;
    _img = img;
}

bool RightParticle::update()
{
    _counter++;
    _x += cos(_angle) * _speed;
    _y += sin(_angle) * _speed;
    float dx = _dstX - _x;
    float dy = _dstY - _y;
    if (dx * dx + dy * dy <= 8*8) {
        return false;
    }
    return true;
}

void RightParticle::draw() const
{
    float a;
    if (_counter<30) {
        a = GetRand(255) * _counter / 30;
    }
    else {
        a = GetRand(255);
    }
    float angle = _angle + randf2(PI/20);
    SetDrawBlendMode(DX_BLENDMODE_ADD, a);
    DrawRotaGraphF(_x, _y, 1.0, angle+PI/2, _img, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
