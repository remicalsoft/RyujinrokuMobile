#pragma once

#include "Singleton.h"
#include <string>
#include <map>
#include "md5.h"

enum eSavedBarrageDataType {
	eSavedBarrageDataType_TryedNum,
	eSavedBarrageDataType_ClearedNum,
}; 

const int SAVED_BARRAGE_DATA_ERROR = -1;

class SavedBarrageData :
	public Singleton<SavedBarrageData>
{

	std::map<std::string, int> _dat;

	void setDefaultValue();

public:
	SavedBarrageData();
	~SavedBarrageData();
	bool load();
	void save();
	void set      (std::string key, eSavedBarrageDataType type, int level, int value);
	void increment(std::string key, eSavedBarrageDataType type, int level);
	int  get      (std::string key, eSavedBarrageDataType type, int level);
	bool isCorrect(std::string str, char hashValue[md5::LENGTH]);
	void getMd5Value(std::string &totalstr, char hashValue[md5::LENGTH]);
};

