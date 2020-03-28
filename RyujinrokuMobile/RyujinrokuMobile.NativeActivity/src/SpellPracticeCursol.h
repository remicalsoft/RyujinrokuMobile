#pragma once
#include "BaseEffectItem.h"

class SpellPracticeCursol : public BaseEffectItem
{
	double _width, _height;
	double _TargetX, _TargetY;
	double _TargetWidth, _TargetHeight;
//	int  _flashCounter, _scrollCounter;
public:
	SpellPracticeCursol(double x, double y,int width,int height);
	bool update() override;
	void draw() override;
	void reset(bool isAvailable);	//カウンタなどをリセット
	void updateTarget(double x,double y);
};

