#include "SavedBarrageData.h"
#include <vector>
#include "BossPrm.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Utils.h"

using namespace std;

const static char*MARKER = "Ryujin2";
const static int DATA_VERSION = 1;
const static char*PATH = "SavedData/SavedDataBarrage.dat";

const std::string savedLevelEasy = "LevelEasy";
const std::string savedLevelNormal = "LevelNormal";
const std::string savedLevelHard = "LevelHard";

const std::vector<std::string> savedDataLevel = {
	savedLevelEasy,
	savedLevelNormal,
	savedLevelHard
};

const std::string savedTryedNum = "TryedNum";
const std::string savedClearedNum = "ClearedNum";

std::string getKeyFromType(eSavedBarrageDataType type) {
	switch (type) {
	case eSavedBarrageDataType_TryedNum:
		return savedTryedNum;
		break;
	case eSavedBarrageDataType_ClearedNum:
		return savedClearedNum;
		break;
	}
	return nullptr;
}

void SavedBarrageData::setDefaultValue()
{
	for (auto i : SPELL_NAME) {
		for (auto name : i) {
			set(name, eSavedBarrageDataType_TryedNum, eLevel_Easy, 0);
			set(name, eSavedBarrageDataType_TryedNum, eLevel_Normal, 0);
			set(name, eSavedBarrageDataType_TryedNum, eLevel_Hard, 0);
			set(name, eSavedBarrageDataType_ClearedNum, eLevel_Easy, 0);
			set(name, eSavedBarrageDataType_ClearedNum, eLevel_Normal, 0);
			set(name, eSavedBarrageDataType_ClearedNum, eLevel_Hard, 0);
		}
	}
}

bool SavedBarrageData::load()
{
	string path = Utils::getSavePath();
	path += PATH;
	std::ifstream ifs(path);
	std::string str;
	std::string totalstr;
	if (ifs.fail())
	{
		return false;
	}
	if (!getline(ifs, str)) {
		return false;
	}
	if (strcmp(str.c_str(), MARKER) != 0) {
		return false;
	}
	if (!getline(ifs, str)) {
		return false;
	}
	int version = -1;
	
	if (str.size()>5) {//ver0.9からのアップデートは当時versionがなかったのでここに入る
		return false;
	}
	try {
		version = stoi(str);
	}
	catch (std::invalid_argument e) {
		return false;
	}
	catch (std::out_of_range e) {
		return false;
	}
	if (version < 0 || 10000 < version) {
		return false;
	}
	std::string hash;
	if (!getline(ifs, hash)) {
		return false;
	}
	while (getline(ifs, str))
	{
		totalstr += str;
		totalstr += "\n";
		vector<string> result;
		Utils::splitString(str, ",", result);
		if (result.size() != 2) {
			ERR("SavedDataBarrage.datのデータが不正です");
		}
		int value = std::atoi(result.at(1).c_str());
		_dat[result.at(0)] = value;
	}
	char hashValue[md5::LENGTH] = {};
	memcpy(hashValue, hash.c_str(), md5::LENGTH);
	if (!isCorrect(totalstr, hashValue)) {
		ERR("!!不正発見!! データの改竄が検出されました");
	}
	return false;
}

void SavedBarrageData::save()
{
	FILE *fp;
	string path = Utils::getSavePath();
	path += PATH;
	fp = fopen(path.c_str(), "w");
	if (fp == NULL) {
		ERR("SavedData/SavedDataBarrage.datに書き込みができませんでした");
	}
	fprintf(fp, "%s\n", MARKER);
	fprintf(fp, "%d\n", DATA_VERSION);
	string totalstr;
	for (auto itr = _dat.begin(); itr != _dat.end(); ++itr) {
		totalstr += itr->first;
		totalstr += ",";
		totalstr += std::to_string(itr->second);
		totalstr += "\n";
	}
	char hashValue[md5::LENGTH] = {0, };
	getMd5Value(totalstr, hashValue);
	for (int i = 0; i < md5::LENGTH; i++) {
		if (hashValue[i] == '\0') {
			break;
		}
		fprintf(fp, "%c", hashValue[i]);
	}
	fprintf(fp, "\n");
	for (auto itr = _dat.begin(); itr != _dat.end(); ++itr) {
		fprintf(fp,"%s,%d\n",itr->first.c_str(),itr->second);
	}
	fclose(fp);
}

SavedBarrageData::SavedBarrageData()
{
	if (!load()) {
		setDefaultValue();
	}
}


SavedBarrageData::~SavedBarrageData()
{
}

void SavedBarrageData::set(std::string key, eSavedBarrageDataType type, int level, int value)
{
	string name = key + getKeyFromType(type) + savedDataLevel[level];
	_dat[name] = value;
}

void SavedBarrageData::increment(std::string key, eSavedBarrageDataType type, int level)
{
	int val = get(key, type, level);
	if (val == SAVED_BARRAGE_DATA_ERROR) {
		return;
	}
	set(key, type, level, val + 1);
}

int SavedBarrageData::get(std::string key, eSavedBarrageDataType type, int level)
{
	if (_dat.find(key + getKeyFromType(type) + savedDataLevel[level]) == _dat.end()) {
		return SAVED_BARRAGE_DATA_ERROR;
	}
	else {
		return _dat[key + getKeyFromType(type) + savedDataLevel[level]];
	}
}

bool SavedBarrageData::isCorrect(string str, char hash[md5::LENGTH])
{
	const char *value = str.c_str();

	md5 md;

	char st[2] = "a";
	char buffer[md5::LENGTH];
	memset(buffer, 0, sizeof(buffer));

	md.initialize();
	for (int i = 0; i < str.size(); i++) {
		st[0] = *value;
		md.add(st);
		value++;
	}
	md.get(buffer);
	md.finalize();
	if (memcmp(buffer, hash, md5::LENGTH) != 0) {
		return false;
	}
	else {
		return true;
	}
	return false;
}

void SavedBarrageData::getMd5Value(std::string &totalstr, char hashValue[md5::LENGTH])
{
	md5 md;
	char st[2] = "a";
	const char *p;
	char md5dat[64];
	memset(md5dat, 0, sizeof(md5dat));
	md.initialize();
	p = totalstr.c_str();
	for (int i = 0; i<totalstr.size(); i++) {
		st[0] = *p;
		p++;
		md.add(st);
	}
	md.get(hashValue);
	md.finalize();
}
