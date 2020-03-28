#include "Bomb.h"
#include <DxLib.h>
#include "SE.h"

Bomb::Bomb(Player* player) {
	_player = player;
	_a = 255;
	_counter = 0;
	_endCounter = 0;
	SE::getIns()->setPlay(eSE::eSE_bom);
}
bool Bomb::update() {
	_laser.update();
	if (_endCounter > 0) {
		_endCounter++;
		if (_endCounter == 64) {
			return false;
		}
	}
	if (_counter >= 180) {
		_a -= 2;
	}
	if (_counter == 180 + 128) {
		return false;
	}
	_counter++;
	return true;
}
void Bomb::draw() {
	SetDrawBlendMode(DX_BLENDMODE_ADD, _a);
	if (_endCounter) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255-_endCounter*4);
	}
	float r = 350;
	if (_counter < 60) {
		r = 350.f * _counter / 60;
	}
	float px = _player->getX(), py = _player->getY();
	_laser.draw(px, py);
	DrawModiGraphF(
		px-r,py-1000,//左上
		px+r,py-1000,//右上
		px+r,py,//右下
		px-r,py,//左下
		Image::getIns()->playerLaserMain, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

float Bomb::getBombR()
{
	return _laser.getR();
}

void Bomb::finish()
{
	_endCounter = 1;
}
