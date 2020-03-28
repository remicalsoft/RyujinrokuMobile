#pragma once
#include "BaseEffectItem.h"

class SpellPracticeIcon : public BaseEffectItem
{
	double _TargetX;
public:
	double getTargetX(){return _TargetX;}
	SpellPracticeIcon(int x, int y,int img);
	bool update() override;
	void updateTargetX(double x){_TargetX = x;}
	void draw() override;
	int getimg() { return _img; }
};