#include <DxLib.h>
#include "SavedData.h"
#include "Define.h"
#include "GameData.h"
#include "md5.h"
#include "Utils.h"

using namespace std;

const static char *MARKER = "Ryujin2";
const static char *PATH = "SavedData/SavedData.dat";

SavedData::SavedData()
{
	if (!load()) {
		setDefaultValue();
	}
}

SavedData::~SavedData()
{
}

bool SavedData::load()
{
	string path = Utils::getSavePath();
	path += PATH;
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		return false;
	}
	int n;
	n = fread(dat.marker, sizeof(dat.marker), 1, fp);
	if (n != 1) {
		ERR("SavedData.datのマーカーを読み取ることができませんでした");
	}
	if (strcmp(dat.marker, MARKER) != 0) {
		ERR("SavedData.datのマーカーが正しくありません");
	}
	fseek(fp, 0, SEEK_SET);
	n = fread(&dat, sizeof(Dat_t), 1, fp);
	if (n != 1) {
		ERR("SavedData.datが正しく読み取れませんでした");
	}
	GameData::getIns()->setMoney(dat.money);
	fclose(fp);
	if (!isCorrectMd5()) {
		ERR("!!不正発見!! データの改竄が検出されました");
	}
	return true;
}

void SavedData::save()
{
	dat.money = GameData::getIns()->getMoney();

	setMd5();

	string path = Utils::getSavePath();
	path += PATH;
	FILE *fp = fopen(path.c_str(), "wb");
	if (fp == NULL) {
		ERR("SavedData.datのファイル出力ができませんでした");
	}
	int n;
	n = fwrite(&dat, sizeof(Dat_t), 1, fp);
	if (n != 1) {
		ERR("SavedData.datのファイル出力が不完全のまま終わりました");
	}
	fclose(fp);
}

void SavedData::setDefaultValue() 
{
	memset(&dat, 0, sizeof(Dat_t));
	strcpy(dat.marker,MARKER);
	dat.version = DATA_VERSION;
}

bool SavedData::isCorrectMd5()
{
	md5 md;

	char st[2] = "a";
	char *p;
	char buffer[md5::LENGTH];
	memset(buffer, 0, sizeof(buffer));

	md.initialize();
	p = (char *)&dat;
	for (int i = 0; i<sizeof(dat) - 64; i++) {
		st[0] = *p;
		p++;
		md.add(st);
	}
	md.get(buffer);
	md.finalize();
	if (memcmp(buffer, dat.hashValue, md5::LENGTH) != 0) {
		return false;
	}
	else {
		return true;
	}
}

void SavedData::setMd5()
{
	md5 md;
	char st[2] = "a";
	char *p;
	char md5dat[64];
	memset(md5dat, 0, sizeof(md5dat));
	md.initialize();
	p = (char *)&dat;
	for (int i = 0; i<sizeof(dat) - 64; i++) {
		st[0] = *p;
		p++;
		md.add(st);
	}
	md.get(dat.hashValue);
	md.finalize();
}

void SavedData::markPlayedMusic(eMusicType type)
{
	dat.havePlayedMusic[type] = true;
}

