#pragma once

enum eItemPopType {
	eItemPopType_PowerSmall,//0
	eItemPopType_PowerLarge,//1
	eItemPopType_PowerMany,	//2
	eItemPopType_ScoreSmall,//3
	eItemPopType_ScoreLaege,//4
	eItemPopType_ScoreMany,	//5
	eItemPopType_MoneySmall,//6
	eItemPopType_MoneyLarge,//7
	eItemPopType_MoneyMany,	//8
	eItemPopType_Bomb,		//9
	eItemPopType_BombParts,	//10

	eItemPopType_Num,
};

class ItemRegistable
{
public:
	ItemRegistable();
	~ItemRegistable();
	virtual void regist(float x, float y, eItemPopType popType) = 0;
};

