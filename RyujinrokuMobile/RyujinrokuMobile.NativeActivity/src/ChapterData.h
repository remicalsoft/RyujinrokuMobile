#pragma once

#include "GameData.h"
#include <DxLib.h>

class ChapterData
{
public:
	bool isBoss;
	int power;
	int bomb;
	int score;
	int point;
	int graze;
	int gameCounter;
	int scoreBreakdown[GameData::eScoreType_Num];
	int preTime;
	int subTime;
	int bossClearNForSaveData;
	eStage stage;
	eLevel level;
	ChapterData() {
		isBoss = false;
		power = 0;
		bomb  = 0;
		score = 0;
		point = 0;
		graze = 0;
		gameCounter = 0;
		for (int i = 0; i < GameData::eScoreType_Num; i++)
		{
			scoreBreakdown[i] = 0;
		}
		preTime = GetNowCount();
		subTime = 0;
		bossClearNForSaveData = 0;
	}
	ChapterData(eStage stage, eLevel level, bool isBoss, int power, int bomb, int score, int point, int graze, int gameCounter,int* scorebreakdown, int bossClearNForSaveData=0) {
		this->stage = stage;
		this->level = level;
		this->isBoss = isBoss;
		this->power = power;
		this->bomb  = bomb;
		this->score = score;
		this->point = point;
		this->graze = graze;
		this->gameCounter = gameCounter;
		for (int i = 0; i < GameData::eScoreType_Num; i++)
		{
			scoreBreakdown[i] = scorebreakdown[i];
		}
		preTime = GetNowCount();
		subTime = 0;
		this->bossClearNForSaveData = bossClearNForSaveData;
	}
	void subPauseTime(int subTime) {
		this->subTime += subTime;
	}
	int getRealPlayTime() {
		int nowTime = GetNowCount();
		int takenTime = nowTime - preTime;
		return takenTime - subTime;
	}
	void save();
	static ChapterData* read(int stage, int level);
	static void remove(int stage, int level);
	static bool exists(int stage, int level);

	void saveReplay();
	static ChapterData* readReplay();
	static void removeReplay();
	static bool existsReplay();
};

