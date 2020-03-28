#include "SmallEnemy.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"

SmallEnemy::SmallEnemy(float x, float y) : AbstractEnemy(x,y)
{
    _movePatternID = 2;
}

void SmallEnemy::draw() const
{
    DrawRotaGraphF(_x, _y, 1.0, PI * 2 / 120 * _counter,        Image::getIns()->getEnemySmall()[0], TRUE);
    DrawRotaGraphF(_x, _y, 1.0, PI * 2 / 120 * (_counter + 60), Image::getIns()->getEnemySmall()[1], TRUE);
}

void SmallEnemy::setSize()
{
    int handle = Image::getIns()->getEnemySmall()[0];
    GetGraphSize(handle, &_width, &_height);
}
