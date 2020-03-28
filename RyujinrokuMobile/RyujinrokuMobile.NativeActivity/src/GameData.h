#pragma once

#include "Singleton.h"
#include "Define.h"
#include "EncryptedInt.h"
#include <string>

using namespace std;

#define DestroyEnemy_BaseScore 1000
#define AttackEnemy_BaseScore 10
#define Graze_BaseScore 100
#define PowerItem_BaseScore 10
#define PointItem_BaseScore 100000
#define GetSpellcard_BaseScore 1000000
#define ChapterClear_BaseScore 2000000
#define EraseBullet_BaseScore 100
#define BombBonus_BaseScore 1000000

class GameData :
	public Singleton<GameData>
{
	EncryptedInt money;
	int itemBorderLineH;

public:

	int power, graze, point, bomb;
	int stage;
	eLevel level;
	float absorbRange;
	bool isPractice;	
	int retryCount;
	int usedBombItemNum;

	enum eScoreType {
		eScoreDestroyEnemy, 
		eScoreAttackEnemy, 
		eScoreGraze, 
		eScorePowerItem, 
		eScorePointItem, 
		eScoreGetSpellcard, 
		eScoreChapterClear,
		eScoreEraseBullet,
		eScoreBombBonus, 
		eScoreType_Num
	};

	int score;
	int scoreBreakdown[eScoreType_Num];	//スコア内訳
	string scoreStr[eScoreType_Num];
	int scoreBase[eScoreType_Num];	//スコア基準点

	GameData();
	~GameData();
	void setMoney(int);
	void addMoney(int);
	int  getMoney();

	void plusScore(double rate, eScoreType type);
	void plusScore(int num, eScoreType type);
	void grazeIncrement();
	int getItemGetBorderLineH();

};

