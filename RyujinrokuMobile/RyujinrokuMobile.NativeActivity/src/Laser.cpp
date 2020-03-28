#include "laser.h"
#include "Utils.h"
#include <DxLib.h>
#include <math.h>
#include "Define.h"
#include "Image.h"

using namespace std;

Laser::Laser()
{
	counter = id = 0;
	width = angle = length = hitWidth = 0;
	handle = 0;
	imgBody = imgRoot = 0;
	color = eLaserColor_Blue;
	isAlive = true;
}

Laser::~Laser()
{
}

bool Laser::update() {
	if (isAlive == false) {
		return false;
	}
	//表示位置を設定
	disppt[0].x = startpt.x + cos(angle + PI / 2)*width;
	disppt[0].y = startpt.y + sin(angle + PI / 2)*width;
	disppt[1].x = startpt.x + cos(angle - PI / 2)*width;
	disppt[1].y = startpt.y + sin(angle - PI / 2)*width;
	disppt[2].x = startpt.x + cos(angle - PI / 2)*width + cos(angle)*length;
	disppt[2].y = startpt.y + sin(angle - PI / 2)*width + sin(angle)*length;
	disppt[3].x = startpt.x + cos(angle + PI / 2)*width + cos(angle)*length;
	disppt[3].y = startpt.y + sin(angle + PI / 2)*width + sin(angle)*length;
	//あたり範囲を設定
	outpt[0].x = startpt.x + cos(angle + PI / 2)*(width*hitWidth) + cos(angle)*length*((1 - hitWidth)*0.3);
	outpt[0].y = startpt.y + sin(angle + PI / 2)*(width*hitWidth) + sin(angle)*length*((1 - hitWidth)*0.3);
	outpt[1].x = startpt.x + cos(angle - PI / 2)*(width*hitWidth) + cos(angle)*length*((1 - hitWidth)*0.3);
	outpt[1].y = startpt.y + sin(angle - PI / 2)*(width*hitWidth) + sin(angle)*length*((1 - hitWidth)*0.3);
	outpt[2].x = startpt.x + cos(angle - PI / 2)*(width*hitWidth) + cos(angle)*length*hitWidth + cos(angle)*length*((1 - hitWidth)*0.7);
	outpt[2].y = startpt.y + sin(angle - PI / 2)*(width*hitWidth) + sin(angle)*length*hitWidth + sin(angle)*length*((1 - hitWidth)*0.7);
	outpt[3].x = startpt.x + cos(angle + PI / 2)*(width*hitWidth) + cos(angle)*length*hitWidth + cos(angle)*length*((1 - hitWidth)*0.7);
	outpt[3].y = startpt.y + sin(angle + PI / 2)*(width*hitWidth) + sin(angle)*length*hitWidth + sin(angle)*length*((1 - hitWidth)*0.7);

	double ymax = lphy.angle, ty = lphy.time, t = counter;
	double delt = (2 * ymax*t / ty - ymax*t*t / (ty*ty));
	if (lphy.time != 0)//回転移動時間内なら
		angle = lphy.base_ang + delt;//回転する
	if (lphy.conv_flag == 1) {//座標変換をするか
		Utils::rotatePos2(&startpt.x, &startpt.y,
			lphy.conv_x, lphy.conv_y,
			lphy.conv_base_x, lphy.conv_base_y,
			-delt);
	}
	if (counter>lphy.time) {//回転時間を過ぎるとやめる
		lphy.time = 0;
		lphy.conv_flag = 0;
	}
	counter++;
	return true;
}

void Laser::draw() {
	switch (color) {
	case eLaserColor_Blue:
		imgRoot = Image::getIns()->laserRoot[eLaserColor_Blue];
		imgBody = Image::getIns()->laserBody[eLaserColor_Blue];
		break;
	case eLaserColor_Pink:
		imgRoot = Image::getIns()->laserRoot[eLaserColor_Pink];
		imgBody = Image::getIns()->laserBody[eLaserColor_Pink];
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawRotaGraphF(//発射位置のエフェクトを描画
		startpt.x, startpt.y, 1.0, 0, imgRoot, TRUE
	);
	DrawModiGraphF(//レーザーを描画
		disppt[0].x, disppt[0].y,
		disppt[1].x, disppt[1].y,
		disppt[2].x, disppt[2].y,
		disppt[3].x, disppt[3].y,
		imgBody, TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*
	Utils::DrawSquare(//当たり判定範囲を表示
		GetColor(255,0,0),
		outpt[0].x, outpt[0].y,
		outpt[1].x, outpt[1].y,
		outpt[2].x, outpt[2].y,
		outpt[3].x, outpt[3].y
	);
	*/
}
