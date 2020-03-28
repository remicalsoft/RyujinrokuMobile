#pragma once

#include "Task.h"
#include "pt_t.h"

enum eLaserColor {
	eLaserColor_Blue,
	eLaserColor_Pink,

	eLaserColor_Num,
};

class Laser :
	public Task
{
public:
	//レーザーの物理的計算を行う為の構造体
	class lphy_t {
	public:
		int conv_flag;//回転するかどうかのフラグ
		float time, base_ang, angle;//回転時間、ベースとなる角度、角度
		float conv_x, conv_y, conv_base_x, conv_base_y;//回転前の座標、回転の基準となる座標
		lphy_t() {
			conv_flag = 0;
			time = base_ang = angle = 0;
			conv_x = conv_y = conv_base_x = conv_base_y = 0;
		}
	};

	int counter, id;//カウンタ
	eLaserColor color;
	float width, angle, length, hitWidth;//幅、角度、長さ、判定範囲(表示幅に対して0~1で指定)
	pt_t startpt, disppt[4], outpt[4];//レーザーを発射する始点、表示座標、当たり判定範囲
	lphy_t lphy;
	int handle;//区別するための識別子
	bool isAlive;
	int imgBody, imgRoot;

	Laser();
	~Laser();
	bool update() override;
	void draw() override;
};

