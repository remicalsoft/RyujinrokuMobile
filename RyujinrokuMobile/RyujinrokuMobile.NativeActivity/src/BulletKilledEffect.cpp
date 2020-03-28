#include "BulletKilledEffect.h"
#include <DxLib.h>
#include "Define.h"

BulletKilledEffect::BulletKilledEffect(float x, float y, eBulletColor color)
{
	this->x = x;
	this->y = y;
	this->_img = ImageBullet::getIns()->get(eBulletType::eTama, color);
	_counter = 0;
}

bool BulletKilledEffect::update()
{
	if (_counter == 40) {
		return false;
	}
	_counter++;
	return true;
}

void BulletKilledEffect::draw()
{
	int c = _counter + 20;
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - 255 / 40.f*_counter);
	DrawRotaGraphF(x, y, sin(PI / 60 * c), 0, _img, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}
