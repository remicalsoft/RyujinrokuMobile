#include "Launcher.h"
#include <DxLib.h>
#include "Utils.h"
#include "Define.h"
#include <math.h>
#include "Image.h"

const static float LEN = 64 * 1.4;

Launcher::Launcher(float firstX, float firstY, float moveX, float moveY, eLauncherType type) {
	img = Image::getIns()->launcherHanabi;
	_type = type;
	this->firstX = firstX;
	this->firstY = firstY;
	this->moveX = moveX;
	this->moveY = moveY;
	init(0, 0, img);
}

Launcher::Launcher(float firstX, float firstY, float moveX, float moveY, int img)
{
	_type = eLauncherType_Normal;
	this->firstX = firstX;
	this->firstY = firstY;
	this->moveX = moveX;
	this->moveY = moveY;
	this->img = img;
	init(0,0,img);
}

Launcher::Launcher(float x, float y, int img) 
{
	_type = eLauncherType_Normal;
	this->x = x;
	this->y = y;
	this->img = img;
	moveX = 0;
	moveY = 0;
	init(x, y, img);
	counter = TIME+1;
}

Launcher::~Launcher()
{
}

void Launcher::init(float x, float y, int img) {
	v = 0;
	ang = 0;
	counter = 0;
	for (int i = 0; i < LAUNCHER_LIGHT_DRAWNUM; i++)
	{
		_a[i] = 255;
		_s[i] = 1;
	}
	id = 0;
	isShooting = false;
	shotCounter = 0;
}

bool Launcher::update()
{
	if (counter<=TIME) {
		x = firstX + sin(PI / 2 / 30 * counter)*moveX;
		y = firstY + sin(PI / 2 / 30 * counter)*moveY;
	}
	else {
		x += cos(ang)*v;
		y += sin(ang)*v;
	}
	if (x<-LEN || OUT_W+ LEN<x || y<-LEN || OUT_H+ LEN<y) {
		return false;
	}
	for (int i = 0; i < LAUNCHER_LIGHT_DRAWNUM; i++) 
	{
		_a[i] = 128 + stdRandf(128);
		_s[i] = 1.0 + stdRandf2(0.4);
	}

	counter++;
	return true;
}

void Launcher::draw()
{
	switch (_type) {
	case eLauncherType_Normal:
		for (int i = 0; i < LAUNCHER_LIGHT_DRAWNUM; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, _a[i]);
			DrawRotaGraphF(x, y, _s[i], 0, img, TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case eLauncherType_Hanabi:
		for (int i = 0; i < LAUNCHER_LIGHT_DRAWNUM; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, _a[i]/2);
			DrawRotaGraphF(x, y, 1.0, 0, img, TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawRotaGraphF(x, y, 1.0, 0, img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}
}
