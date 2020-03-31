#include <math.h>
#include "MathUtils.h"
#include <DxLib.h>
#include "Define.h"

using namespace std;

/*
* @brief 0~valまでの乱数を返す
*/
float randf(float val) {
	return GetRand(1000000) / 1000000.f * val;
}

/*
* @brief -val~valまでの乱数を返す
*/
float randf2(float val) {
	return GetRand(1000000) / 500000.f * val - val;
}

//srcに対するdstの角度を返す
float MathUtils::getAngle(float srcX, float srcY, float dstX, float dstY)
{
	float dx = dstX - srcX;
	float dy = dstY - srcY;
	if (dx == 0 && dy == 0) {	//両方０なら０を返すことにする
		return 0;
	}
	else {
		return atan2(dy, dx);
	}
}

/*
*@brief valの小数点第point位を四捨五入して丸める
*/
float MathUtils::roundPoint(float val, int point) {
	float ret;
	ret = val * pow(10.f, +point - 1);
	ret = (float)(int)(ret + 0.5f);
	return ret * pow(10.f, -point + 1);
}
