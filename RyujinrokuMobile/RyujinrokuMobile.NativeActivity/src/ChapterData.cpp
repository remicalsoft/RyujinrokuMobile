#include "ChapterData.h"
#include "Define.h"
#include "Utils.h"
#include "Replayer.h"

const static char* CHAPTER_FILE[eStage_Num][eLevel_Num] = {
	{
		CHAPTER_DATA_FILE_EASY_1,
		CHAPTER_DATA_FILE_NORMAL_1,
		CHAPTER_DATA_FILE_HARD_1,
	},
	{
		CHAPTER_DATA_FILE_EASY_1,
		CHAPTER_DATA_FILE_NORMAL_1,
		CHAPTER_DATA_FILE_HARD_1,
	},
	{
		CHAPTER_DATA_FILE_EASY_1,
		CHAPTER_DATA_FILE_NORMAL_1,
		CHAPTER_DATA_FILE_HARD_1,
	},
	{
		CHAPTER_DATA_FILE_EASY_1,
		CHAPTER_DATA_FILE_NORMAL_1,
		CHAPTER_DATA_FILE_HARD_1,
	},
	{
		CHAPTER_DATA_FILE_EASY_1,
		CHAPTER_DATA_FILE_NORMAL_1,
		CHAPTER_DATA_FILE_HARD_1,
	},
	{
		CHAPTER_DATA_FILE_EASY_EX,
		CHAPTER_DATA_FILE_NORMAL_EX,
		CHAPTER_DATA_FILE_HARD_EX,
	},
	{
		CHAPTER_DATA_FILE_EASY_PH,
		CHAPTER_DATA_FILE_NORMAL_PH,
		CHAPTER_DATA_FILE_HARD_PH,
	}
};

void ChapterData::save()
{
	if (Replayer::getIns()->isReplaying()) {
		saveReplay();
		return;
	}

	string path = Utils::getSavePath();
	path += CHAPTER_FILE[stage][level];
	FILE *fp = fopen(path.c_str(), "wb");
	if (fp == NULL) {
		ERR("チャプターデータが書き込めませんでした");
	}
	fwrite(this, sizeof(ChapterData), 1, fp);
	fclose(fp);
}

ChapterData* ChapterData::read(int stage, int level)
{
	if (Replayer::getIns()->isReplaying()) {
		return readReplay();
	}

	ChapterData* dat = new ChapterData;
	string path = Utils::getSavePath();
	path += CHAPTER_FILE[stage][level];
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		return nullptr;
	}
	fread(dat, sizeof(ChapterData), 1, fp);
	fclose(fp);
	dat->preTime = GetNowCount();
	dat->subTime = 0;
	return dat;
}

void ChapterData::remove(int stage, int level)
{
	if (Replayer::getIns()->isReplaying()) {
		removeReplay();
	}

	if (exists(stage,level)) {
		ChapterData* dat = new ChapterData;
		string path = Utils::getSavePath();
		path += CHAPTER_FILE[stage][level];;
		DeleteFile(path.c_str());
	}
}

bool ChapterData::exists(int stage, int level)
{
	string path = Utils::getSavePath();
	path += CHAPTER_FILE[stage][level];
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		return false;
	}
	fclose(fp);
	return true;
}

void ChapterData::saveReplay()
{
	string path = Utils::getSavePath();
	path += CHAPTER_REPLAY_DATA_FILE;
	FILE *fp = fopen(path.c_str(), "wb");
	if (fp == NULL) {
		ERR("チャプターデータが書き込めませんでした");
	}
	fwrite(this, sizeof(ChapterData), 1, fp);
	fclose(fp);
}

ChapterData * ChapterData::readReplay()
{
	ChapterData* dat = new ChapterData;
	string path = Utils::getSavePath();
	path += CHAPTER_REPLAY_DATA_FILE;
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		return nullptr;
	}
	fread(dat, sizeof(ChapterData), 1, fp);
	fclose(fp);
	dat->preTime = GetNowCount();
	dat->subTime = 0;
	return dat;
}

void ChapterData::removeReplay()
{
	if (existsReplay()) {
		ChapterData* dat = new ChapterData;
		string path = Utils::getSavePath();
		path += CHAPTER_REPLAY_DATA_FILE;
		DeleteFile(path.c_str());
	}
}

bool ChapterData::existsReplay()
{
	string path = Utils::getSavePath();
	path += CHAPTER_REPLAY_DATA_FILE;
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		return false;
	}
	fclose(fp);
	return true;
}
