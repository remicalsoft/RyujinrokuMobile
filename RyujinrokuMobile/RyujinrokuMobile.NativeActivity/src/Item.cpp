#include "Item.h"
#include "Define.h"
#include "Image.h"
#include <DxLib.h>

const static int H = 70;

Item::Item(float x, float y, eItemType type)
{
	_x = x;
	_y = y;
	_counter = 0;
	_type = type;
	_v = -5;
	_angleAbsorbe = PI / 2;
	_vAbsorbe = 10;
	_scale = 1.0f;
	_range = 50;
	_isAuto = false;
	switch (type) {
	case eItemType_PowerSmall:
		_scale = 0.5f;
		_range *= 0.7;
		//fall
	case eItemType_PowerLarge:
		_image = Image::getIns()->item[eItem_Power];
		break;
	case eItemType_ScoreSmall:
		_scale = 0.5f;
		_range *= 0.7;
		//fall
	case eItemType_ScoreLarge:
		_image = Image::getIns()->item[eItem_Score];
		break;
	case eItemType_MoneySmall:
		_scale = 0.5f;
		_range *= 0.7;
		//fall
	case eItemType_MoneyLarge:
		_image = Image::getIns()->item[eItem_Money];
		break;
	case eItemType_Empty:
		_image = Image::getIns()->item[eItem_Empty];
		_range *= 0.5;
		break;
	case eItemType_Bomb:
		_image = Image::getIns()->item[eItem_Bomb];
		break;
	case eItemType_BombParts:
		_image = Image::getIns()->item[eItem_BombParts];
		break;
	}
}

Item::~Item()
{
}

bool Item::update()
{
	_counter++;
	if (_y > OUT_H+H/2) {
		return false;
	}
	if (_isAuto) {
		static const int V = 15;
		_x += cos(_angleAbsorbe)*V;
		_y += sin(_angleAbsorbe)*V;
	}
	if (_v < 3.5) {
		_v += 0.08;
	}
	if (_isAbsorbing) {
		_x += cos(_angleAbsorbe)*_vAbsorbe;
		_y += sin(_angleAbsorbe)*_vAbsorbe;
	}
	else {
		_y += _v;
	}
	return true;
}

void Item::draw()
{
	DrawRotaGraphF(_x, _y, _scale,     +PI * 2 / 360 * _counter, _image[1], TRUE);
	DrawRotaGraphF(_x, _y, _scale*0.5, -PI * 2 / 360 * _counter, _image[1], TRUE);
	DrawRotaGraphF(_x, _y, _scale,     0,                        _image[0], TRUE);
}
