#include "SpellPracticeIcon.h"
#include "DxLib.h"
#include "Define.h"

extern void num_near2(double* val,double target,double rate, double delta);

SpellPracticeIcon::SpellPracticeIcon(int x, int y,int img) : BaseEffectItem(x,y,img, true)
{
	int w, h;
	_img = img;
	GetGraphSize(img, &w, &h);

	_TargetX= x -w/2;
}

bool SpellPracticeIcon::update(){
	BaseEffectItem::update();

	num_near2(&_x, _TargetX, 0.3, 10);

	if(_x >= WIN_W*(eStage_Num-1)*2)
	{
		_x -= WIN_W*eStage_Num;
		_TargetX -= WIN_W*eStage_Num;
	}
	if(_x <= -WIN_W*(eStage_Num-1)*2)
	{
		_x += WIN_W*eStage_Num;
		_TargetX += WIN_W*eStage_Num;
	}
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

void SpellPracticeIcon::draw(){
	for(int i=0; i<3; i++)
	{
		int x= _x;
		x += (i-1)*WIN_W*eStage_Num;	//まるまる１ループ分ずらす
		if(-WIN_W <= x && x < WIN_W)	//３画面分以内にいたら描画
			DrawGraph(x, _y, _img, TRUE);
	}
}
