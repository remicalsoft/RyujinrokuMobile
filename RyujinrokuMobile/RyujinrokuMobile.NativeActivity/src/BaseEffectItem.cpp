#include "BaseEffectItem.h"
#include <DxLib.h>


BaseEffectItem::BaseEffectItem(double x,double y,int img, bool isAvailable) : BaseItem(x,y,img,isAvailable)
{
	_isFinalized = false;
	_isCanceled = false;
	_cancelCounter = 0;
	_immutableCounter = 0;
}

void BaseEffectItem::reset(bool isAvailable)	//カウンタをリセット
{
	BaseItem::reset(isAvailable);
	_isFinalized = false;
	_isCanceled = false;
	_cancelCounter = 0;
	_immutableCounter = 0;
}


void BaseEffectItem::finalize(){
	_isFinalized = true;
}

void BaseEffectItem::cancel()
{
	_isCanceled = true;
}

bool BaseEffectItem::update(){
	BaseItem::update();

	_immutableCounter++;

	return true;
}

