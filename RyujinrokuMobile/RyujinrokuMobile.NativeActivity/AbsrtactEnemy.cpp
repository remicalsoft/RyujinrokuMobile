#include "AbstractEnemy.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"

AbstractEnemy::AbstractEnemy(float x, float y) : 
    _x(x), 
    _y(y), 
    _speed(0), 
    _angle(0), 
    _counter(0),
    _width(0),
    _height(0),
    _movePatternID(0)
{
}

void AbstractEnemy::initialize()
{
    setSize();
}

bool AbstractEnemy::update()
{
    _mover.move(this);
    _counter++;
    return isInside();
}

/*!
@brief 現在の位置が画面内か？
*/
bool AbstractEnemy::isInside() const
{
    if (_counter < 60) {//最初の1秒は判定しない
        return true;
    }
    if (_x < -_width/2 || Define::FIELD_W + _width/2 < _x || _y < -_height/2 || Define::FIELD_H + _height/2 < _y) {
        return false;
    }
    return true;
}
