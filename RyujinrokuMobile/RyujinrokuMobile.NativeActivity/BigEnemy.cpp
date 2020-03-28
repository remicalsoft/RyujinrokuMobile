#include "BigEnemy.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"
#include <math.h>

BigEnemy::BigEnemy(float x, float y) : AbstractEnemy(x, y)
{
    _movePatternID = 0;
}

void BigEnemy::draw() const
{
    const static int imgID[4] = { 0,1,2,1 };
    int add = 3;
    if (cos(_angle)>0.1) {//右向き
        add = 6;
    }
    if (cos(_angle)<-0.1) {//左向き
        add = 0;
    }
    const int handle = Image::getIns()->getEnemyBig()[add + imgID[(_counter / 8) % 4]];
    DrawRotaGraphF(_x, _y, 1.0, 0.0, handle, TRUE);
}

void BigEnemy::setSize()
{
    int handle = Image::getIns()->getEnemyBig()[0];
    GetGraphSize(handle, &_width, &_height);
}
