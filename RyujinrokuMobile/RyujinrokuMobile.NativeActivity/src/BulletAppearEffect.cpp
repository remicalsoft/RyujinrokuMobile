#include "BulletAppearEffect.h"
#include "Image.h"
#include <DxLib.h>

BulletAppearEffect::BulletAppearEffect(float x, float y) : BulletEffect(x, y) {
}

bool BulletAppearEffect::update(){
	_counter++;
	if (_counter > 20) {
		return false;
	}
	return true;
}

void BulletAppearEffect::draw(){
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	if (_counter>15) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - ((_counter - 15) * 51));
	}
	DrawRotaGraphF(_x, _y, 1.0+_counter / 10., 0, Image::getIns()->bulletDisappear, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
