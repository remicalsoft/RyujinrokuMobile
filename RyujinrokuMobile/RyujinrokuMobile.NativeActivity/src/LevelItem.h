#pragma once
#include "BaseEffectItem.h"

class LevelItem : public BaseEffectItem
{
	int  _flashCounter, _scrollCounter;
public:
	LevelItem(int x, int y,int img ,bool isAvailable);
	bool update() override;
	void draw() override;
	void reset(bool isAvailable);	//カウンタなどをリセット
	void skipScroll();
};

