#pragma once
#include "Task.h"
#include "ItemRegistable.h"

enum eItem {
	eItem_Power,
	eItem_Score,
	eItem_Money,
	eItem_Empty,
	eItem_Bomb,
	eItem_BombParts,

	eItem_Num,
};

enum eItemType {
	eItemType_PowerSmall,//0
	eItemType_PowerLarge,//1
	eItemType_ScoreSmall,//2
	eItemType_ScoreLarge,//3
	eItemType_MoneySmall,//4
	eItemType_MoneyLarge,//5
	eItemType_Empty,	 //6
	eItemType_Bomb,      //7
	eItemType_BombParts, //8

	eItemType_Num,
};

class Item :
	public Task
{
	float _x, _y, _v, _angleAbsorbe, _vAbsorbe, _scale;
	int *_image;
	int _counter;
	float _range;
	bool _isAbsorbing, _isAuto;
	eItemType _type;
public:
	Item(float x, float y, eItemType type);
	~Item();
	bool update() override;
	void draw() override;
	float getX() {
		return _x;
	}
	float getY() {
		return _y;
	}
	float getRange() {
		return _range;
	}
	eItemType getItemType() {
		return _type;
	}
	void setAngle(float angle) {
		_angleAbsorbe = angle;
	}

//	bool getIsAbsorb() { return _isAbsorbing; }
	void setIsAbsorb(bool isEnabled) {
		_isAbsorbing = isEnabled;
	}
	bool isAuto() {
		return _isAuto;
	}
	void setAuto() {
		_isAuto = true;
	}
};

