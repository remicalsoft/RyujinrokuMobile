#include "NormalEnemy.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"

NormalEnemy::NormalEnemy(float x, float y) : AbstractEnemy(x,y)
{
    _movePatternID = 1;
}

void NormalEnemy::draw() const
{
    const static int imgID[4] = { 0,1,2,1 };
    int add = 3;
    if (cos(_angle)>0.1) {//右向き
        add = 6;
    }
    if (cos(_angle)<-0.1) {//左向き
        add = 0;
    }
    const int handle = Image::getIns()->getEnemyNormal()[add + imgID[(_counter / 8) % 4]];
    DrawRotaGraphF(_x, _y, 1.0, 0.0, handle, TRUE);
}

void NormalEnemy::setSize()
{
    int handle = Image::getIns()->getEnemyNormal()[0];
    GetGraphSize(handle, &_width, &_height);
}
