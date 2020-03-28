#include "GameData.h"
#include <DxLib.h>
#include "SavedData.h"

GameData::GameData()
{
	score = 0;
	point = 0;
	power = 0;
	graze = 0;
	score = 0;
	usedBombItemNum = 0;
	bomb = BOMB_PARTS_N * 1 + BOMB_PARTS_N - 1;
	absorbRange = 110;
	stage = 0;
	isPractice=false;
	retryCount = 0;
	level = eLevel_Easy;
//	level = eLevel_Normal;
//	level = eLevel_Hard;
	itemBorderLineH = 230;

	for (int i = 0; i < eScoreType_Num; i++)
	{
		scoreBreakdown[i] = 0;
	}


	scoreStr[eScoreDestroyEnemy] ="敵撃破";
	scoreStr[eScoreAttackEnemy] = "敵攻撃";
	scoreStr[eScoreGraze] = "グレイズ";
	scoreStr[eScorePowerItem] = "Pアイテム";
	scoreStr[eScorePointItem] = "点アイテム";
	scoreStr[eScoreGetSpellcard] = "スペカ取得";
	scoreStr[eScoreChapterClear] = "チャプタークリア";
	scoreStr[eScoreEraseBullet] = "弾消し";
	scoreStr[eScoreBombBonus] = "ボムボーナス";

	scoreBase[eScoreDestroyEnemy] = DestroyEnemy_BaseScore;
	scoreBase[eScoreAttackEnemy] = AttackEnemy_BaseScore;
	scoreBase[eScoreGraze] = Graze_BaseScore;
	scoreBase[eScorePowerItem] = PowerItem_BaseScore;
	scoreBase[eScorePointItem] = PointItem_BaseScore;
	scoreBase[eScoreGetSpellcard] = GetSpellcard_BaseScore;
	scoreBase[eScoreChapterClear] = ChapterClear_BaseScore;
	scoreBase[eScoreEraseBullet] = EraseBullet_BaseScore;
	scoreBase[eScoreBombBonus] = BombBonus_BaseScore;


}


GameData::~GameData()
{
}

void GameData::setMoney(int value)
{
	money.set(value);
}

void GameData::addMoney(int value)
{
	setMoney(money.get() + value);
}

int GameData::getMoney()
{
	return money.get();
}

void GameData::plusScore(double rate, eScoreType type)
{
	score += int(scoreBase[type]* rate);
	scoreBreakdown[type] += int(scoreBase[type]* rate);
}
void GameData::plusScore(int num, eScoreType type)
{
	score += num;
	scoreBreakdown[type] += num;
}

void GameData::grazeIncrement() {
	graze++;
	plusScore(1.0, GameData::eScoreGraze);
}

int GameData::getItemGetBorderLineH()
{
	float lineY = itemBorderLineH;
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Hoseki]) {
		lineY += 60;
	}
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Hoseki2]) {
		lineY += 60;
	}
	return lineY;
}
