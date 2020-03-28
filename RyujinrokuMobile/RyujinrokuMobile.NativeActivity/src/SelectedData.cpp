#include "SelectedData.h"
#include <string>
#include "Utils.h"
#include "Define.h"

using namespace std;

constexpr char* PATH = "SavedData/level.dat";

SelectedData::SelectedData()
{
}

SelectedData::~SelectedData()
{
}

void SelectedData::save(int level)
{
	string path = Utils::getSavePath();
	path += PATH;
	FILE *fp = fopen(path.c_str(), "wb");
	if (fp == NULL) {
		ERR("チャプターデータが書き込めませんでした");
	}
	fwrite(&level, sizeof(int), 1, fp);
	fclose(fp);
}

int SelectedData::read()
{
	string path = Utils::getSavePath();
	path += PATH;
	int level = 0;
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		return -1;
	}
	fread(&level, sizeof(int), 1, fp);
	fclose(fp);
	return level;
}
