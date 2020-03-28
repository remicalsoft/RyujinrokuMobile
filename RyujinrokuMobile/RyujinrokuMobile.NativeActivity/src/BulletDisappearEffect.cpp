#include "BulletDisappearEffect.h"
#include "Image.h"

bool BulletDisappearEffect::update(){
	_counter++;
	if (_counter > 20) {
		return false;
	}
	return true;
}

void BulletDisappearEffect::draw(){
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	if (_counter>15) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - ((_counter - 15) * 51));
	}
	DrawRotaGraphF(_x, _y, _counter / 10., 0, Image::getIns()->bulletDisappear, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
