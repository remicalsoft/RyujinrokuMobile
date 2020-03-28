#include "SpellPracticeCursol.h"
#include <DxLib.h>
#include "Utils.h"
#include "Define.h"
#include "math.h"

SpellPracticeCursol::SpellPracticeCursol(double x, double y,int width,int height) : BaseEffectItem(0,0,0,true)
{
	_width = WIN_W;
	_height = WIN_H;
	_TargetX = x;
	_TargetY = y;
	_TargetWidth = width;
	_TargetHeight = height;

//	_flashCounter = 0;
//	_scrollCounter = 0;
}

void SpellPracticeCursol::reset(bool isAvailable)	//カウンタをリセット
{
	BaseEffectItem::reset(isAvailable);
//	_flashCounter = 0;
//	_scrollCounter = 0;
}

//変数をある数値に少しづつ近付ける関数
void num_near(double* val,double target,double delta)
{
	if(fabs(*val-target)<=delta)
		*val=target;
	else
	{
		*val += ((target-*val>0)*2-1)*delta;
	}
}
//変数をある数値に少しづつ近付ける関数  遠いほど近づくのが早くなる速度可変ver
void num_near2(double* val,double target,double rate, double delta)
{
	num_near(val,target,delta+(*val-target)*(*val-target)/1000*rate);
}

bool SpellPracticeCursol::update(){
	BaseEffectItem::update();

	num_near2(&_x, _TargetX, 1, 3);
	num_near2(&_y, _TargetY, 1, 3);
	num_near2(&_width, _TargetWidth, 1, 3);
	num_near2(&_height, _TargetHeight, 1, 3);
	/*
	if (_isFinalized) {
		_flashCounter++;
		if (_flashCounter > 16) {
			_scrollCounter++;
		}
	}
	if (_isCanceled) {
		_cancelCounter++;
		if (_cancelCounter > 16) {
			_scrollCounter++;
		}
	}
	*/
	return true;
}

void SpellPracticeCursol::updateTarget(double x,double y)
{
	_TargetX = x;
	_TargetY = y;
}

void SpellPracticeCursol::draw(){
	int size= 2;

	DrawBox(_x-size,0, _x, WIN_H, GetColor(255, 0, 0), TRUE);
	DrawBox(_x+ _width,0, _x+_width+size, WIN_H, GetColor(255, 0, 0), TRUE);

	DrawBox(0,_y-size, WIN_W, _y, GetColor(255, 0, 0), TRUE);
	DrawBox(0,_y+ _height, WIN_W, _y+_height+size, GetColor(255, 0, 0), TRUE);

}
