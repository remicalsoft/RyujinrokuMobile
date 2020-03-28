#pragma once
#include "Task.h"
class BaseItem : public Task
{
protected:
	int  _img;
	double  _x, _y;
	int  _counter;
	bool _isAvailable;
public:
	BaseItem(double x, double y,int img ,bool isAvailable);
	~BaseItem();
	virtual void enable();
	virtual void disable();
	bool update() override;
	void draw() override;
	void reset(bool isAvailable);	//カウンタなどをリセット
	void setPos(float x, float y);
};

