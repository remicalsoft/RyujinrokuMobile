#include "PlayerShotStraight.h"
#include "Define.h"
#include "Image.h"
#include <DxLib.h>

const static float V = 70;
const static int H = 92;

PlayerShotStraight::PlayerShotStraight(float x, float y, float power) : PlayerShot(x,y,power) {
	_angle = -PI / 2;
	_v = V;
	_image = Image::getIns()->playerShot00;
	_range = 18;
}

PlayerShotStraight::~PlayerShotStraight()
{
}

bool PlayerShotStraight::update()
{
	PlayerShot::update();
	if (_y < -H / 2) {
		return false;
	}
	return true;
}

void PlayerShotStraight::draw(){
	DrawRotaGraph(_x, _y, 1.0, 0, _image, TRUE);
}
