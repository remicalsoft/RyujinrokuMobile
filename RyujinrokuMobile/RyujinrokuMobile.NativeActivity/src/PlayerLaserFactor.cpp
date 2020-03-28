#include "PlayerLaserFactor.h"
#include <DxLib.h>
#include "Image.h"

PlayerLaserFactor::PlayerLaserFactor(float y) {
	img = Image::getIns()->playerLaser[GetRand(4)];
	this->x = 0;
	this->y = y;
	this->size = 1;
}
void PlayerLaserFactor::update() {
	y -= 15;
	if (y<-1000) {
		y += 1000;
	}
}
void PlayerLaserFactor::draw(float sx, float sy) {
	DrawRotaGraph(x + sx, y + sy, size, 0, img, TRUE);
}
