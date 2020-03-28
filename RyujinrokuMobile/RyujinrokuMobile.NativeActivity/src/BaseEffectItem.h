#pragma once

#include "BaseItem.h"

class BaseEffectItem : public BaseItem
{
protected:
	int  _immutableCounter, _cancelCounter;
	bool _isFinalized, _isCanceled;
public:
	BaseEffectItem(double x, double y,int img ,bool isAvailable);
	void finalize() override;
	void cancel();
	bool update() override;
	void reset(bool isAvailable);	//カウンタなどをリセット
};

