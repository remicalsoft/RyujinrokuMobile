#include "BossDeathParticle.h"
#include "Utils.h"
#include <DxLib.h>
#include "Define.h"
#include "Image.h"

BossDeathParticle::BossDeathParticle(float x, float y)
{
	_x = x;
	_y = y;
	_v = 2 + randf(15);
	_ang = randf2(PI);
	_a = 255;
	_counter = 0;
}

BossDeathParticle::~BossDeathParticle()
{
}

bool BossDeathParticle::update()
{
	_a -= 2;
	_x += cos(_ang) * _v;
	_y += sin(_ang) * _v;
	if (_a <= 0) {
		return false;
	}
	return true;
}

void BossDeathParticle::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, (int)_a);
	DrawRotaGraphF(_x, _y, 1.0 * _a / 255, 0.0, Image::getIns()->bossDeathParticle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
