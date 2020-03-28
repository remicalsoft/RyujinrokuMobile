#include "Bullet.h"
#include <math.h>
#include <DxLib.h>
#include "Define.h"
#include "ImageBullet.h"

Bullet::Bullet(bullet_t *b) {
	dat = *b;
	dat.range = BULLET_RANGE[dat.type];
}


Bullet::~Bullet()
{
}

bool Bullet::update()
{
	dat.x += cos(dat.ang)*dat.v;
	dat.y += sin(dat.ang)*dat.v;
	dat.counter++;
	const wh_t* size = ImageBullet::getIns()->getSize(dat.type);
	float len = size->w > size->h ? size->w : size->h;
	if (dat.kill) {
		return false;
	}
	if (-len/2 < dat.x && dat.x <= OUT_W+len/2 && -len/2 < dat.y && dat.y <= OUT_H+len/2
		&& dat.isAlive || dat.keepAlive || dat.counter<60) {
		return true;
	}
	else {
		return false;
	}
}

void Bullet::draw(){
	if (dat.isAddBlend || dat.type == eBulletType::eLaser) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, dat.a);
	}
	else if (dat.a != 255) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, dat.a);
	}
	if (dat.type == eBulletType::eStar) {
		DrawRotaGraphF(dat.x, dat.y, dat.size, PI2/180*dat.counter, ImageBullet::getIns()->get(dat.type, dat.color), TRUE);
	}
	else {
		DrawRotaGraphF(dat.x, dat.y, dat.size, PI / 2 + dat.ang, ImageBullet::getIns()->get(dat.type, dat.color), TRUE);
	}
	if (dat.isAddBlend || dat.type == eBulletType::eLaser) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (dat.a != 255) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}
