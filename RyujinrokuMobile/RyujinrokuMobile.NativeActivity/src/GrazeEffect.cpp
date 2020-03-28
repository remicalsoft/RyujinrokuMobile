#include "GrazeEffect.h"
#include <DxLib.h>
#include "Utils.h"
#include "Define.h"
#include "Image.h"

GrazeEffect::GrazeEffect(float x, float y)
{
	this->_x = x;
	this->_y = y;
	_v = 6;
	_a = 255;
	_ang = randf2(PI);
}

GrazeEffect::~GrazeEffect()
{
}

bool GrazeEffect::update()
{
	_v-=0.1;
	_a -= 255.0 / 60;
	_x += cos(_ang)*_v;
	_y += sin(_ang)*_v;
	if (_v<=0) {
		return false;
	}
	return true;
}

void GrazeEffect::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _a);
	DrawRotaGraph(_x, _y, 1.0, 0, Image::getIns()->graze, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
