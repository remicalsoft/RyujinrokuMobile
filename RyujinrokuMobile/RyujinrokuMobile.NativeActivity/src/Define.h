#pragma once

#include "Error.h"

#define CAM_DIST   100.f	//カメラの手前
#define CAM_FAR  10000.f	//カメラの奥
#define WIN_W 1280
#define WIN_H 960
#define COLOR_BIT 32
#define OUT_W 896
#define OUT_H 960
#define IN_W 770
#define IN_H 880
#define CENTER_X (OUT_W/2)
#define CENTER_Y (OUT_H/2)
#define IN_X ((OUT_W - IN_W) / 2)
#define IN_Y ((OUT_H - IN_H) / 2)
#define PI 3.141592654f
#define PI2 (3.141592654f*2)
#define LEVEL_NUM 3
#define FONT "メイリオ"
#define KEY_REPERT 22
#define KEY_REPERT_ITVL 3
#define BOMB_PARTS_N 3

#define ERR(str) Error::finalize(str,_T(__FUNCTION__),__LINE__)

#define VERSION "01.00.02"

#define CHAPTER_DATA_FILE_EASY_1   "SavedData/ChapterEasy1.dat"
#define CHAPTER_DATA_FILE_NORMAL_1 "SavedData/ChapterNormal1.dat"
#define CHAPTER_DATA_FILE_HARD_1   "SavedData/ChapterLunatic1.dat"
#define CHAPTER_DATA_FILE_EASY_EX   "SavedData/ChapterEasy6.dat"
#define CHAPTER_DATA_FILE_NORMAL_EX "SavedData/ChapterNormal6.dat"
#define CHAPTER_DATA_FILE_HARD_EX   "SavedData/ChapterLunatic6.dat"
#define CHAPTER_DATA_FILE_EASY_PH   "SavedData/ChapterEasy7.dat"
#define CHAPTER_DATA_FILE_NORMAL_PH "SavedData/ChapterNormal7.dat"
#define CHAPTER_DATA_FILE_HARD_PH   "SavedData/ChapterLunatic7.dat"
#define CHAPTER_REPLAY_DATA_FILE    "SavedData/ChapterReplay.dat"

enum eLevel {
	eLevel_Easy,
	eLevel_Normal,
	eLevel_Hard,

	eLevel_Num,
};

enum eStage {
	eStage1,
	eStage2,
	eStage3,
	eStage4,
	eStage5,
	eStageEX,
	eStagePH,

	eStage_Num,
};

class Posf {
public:
	float x, y;
	Posf() {
		x = 0;
		y = 0;
	}
	Posf(float x, float y) {
		this->x = x;
		this->y = y;
	}
};
