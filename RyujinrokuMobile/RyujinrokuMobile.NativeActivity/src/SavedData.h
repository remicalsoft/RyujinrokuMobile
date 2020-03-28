#pragma once

#include <map>
#include <string>
#include "Define.h"
#include "Singleton.h"
#include <vector>
#include "StoreBuyKeyScene.h"
#include "StoreBuyScene.h"
#include "md5.h"
#include "MusicRoomScene.h"

enum eSelectType {
	eSelectType_Easy_1,
	eSelectType_Easy_EX,
	eSelectType_Easy_PH,
	eSelectType_Normal_1,
	eSelectType_Normal_EX,
	eSelectType_Normal_PH,
	eSelectType_Hard_1,
	eSelectType_Practice1,
	eSelectType_Practice2,
	eSelectType_Practice3,
	eSelectType_Practice4,
	eSelectType_Practice5,
	eSelectType_OmakeDanmaku,

	eSelectType_NUM,
};

class SavedData : public Singleton<SavedData>
{

	const static int DATA_VERSION = 0;

public:
	typedef struct {
		char marker[8];
		int  version;
		bool isClearStage[eLevel_Num][eStage_Num];
		bool havePlayed[eStage_Num];
		bool havePlayedMusic[MusicRoomScene::MUSIC_NUM];
		int  totalPlayTime;
		int  hiScore[eLevel_Num][eStage_Num];
		int  money;
		bool hasEquipableItem[STORE_EQUIPABLEITEM_MAX];
		bool isEquiped[STORE_EQUIPABLEITEM_MAX];
		bool hasBarrageKey[STORE_BARRAGE_KEY_MAX];
		int  playedNPerSelect[eSelectType_NUM];
        int  isPremium;
		int  reserve[999];
		char hashValue[md5::LENGTH];
	} Dat_t;

	Dat_t dat;

	SavedData();
	~SavedData();

	bool load();
	void save();
	void setDefaultValue();
	bool isCorrectMd5();
	void setMd5();

	void markPlayedMusic(eMusicType type);
};
