#include "PlayerShotTail.h"
#include "Image.h"
#include "Define.h"
#include "Calculator.h"

const static int W = 160;
const static int H = 160;

PlayerShotTail::PlayerShotTail(float x, float y, float power) : PlayerShot(x, y, power)
{
	_angle = -PI/2;
	_v = 50;
	_image = Image::getIns()->playerShot01;
	_range = 20;
}


PlayerShotTail::~PlayerShotTail()
{
}

bool PlayerShotTail::update()
{
	Posf pos = Calculator::getIns()->getNearestEnemyPos(_x, _y);
	if (pos.x == -1 && pos.y == -1) {
		//nothing
	}
	else {
		_angle = atan2(pos.y - _y, pos.x - _x);
	}
	PlayerShot::update();
	if (_y < -H / 2 || _y > H / 2 + OUT_H || _x < -W / 2 || _x > W / 2 + OUT_W) {
		return false;
	}
	return true;
}

void PlayerShotTail::draw()
{
	DrawRotaGraph(_x, _y, 1.0, _angle+PI/2, _image, TRUE);
}
