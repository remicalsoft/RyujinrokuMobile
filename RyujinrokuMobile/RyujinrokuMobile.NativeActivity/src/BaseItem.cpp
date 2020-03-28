#include "BaseItem.h"
#include <DxLib.h>


BaseItem::BaseItem(double x,double y,int img, bool isAvailable)
{
	int w=0, h=0;
	_img = img;
	GetGraphSize(img, &w, &h);
	_x = x - w/2;
	_y = y - h/2;
	_counter = -1;
	_isAvailable = isAvailable;
}

void BaseItem::reset(bool isAvailable)	//カウンタをリセット
{
	_counter = -1;
	_isAvailable = isAvailable;
}

void BaseItem::setPos(float x, float y)
{
	_x = x;
	_y = y;
}

BaseItem::~BaseItem()
{
}


void BaseItem::enable()
{
	_counter = 0;
	_isAvailable = true;
}

void BaseItem::disable()
{
	_counter = -1;
	_isAvailable = false;
}


bool BaseItem::update(){
	if (_counter >= 0) {
		_counter++;
	}
	return true;
}


void BaseItem::draw(){
		DrawGraph((int)_x , (int)_y, _img, TRUE);
}
