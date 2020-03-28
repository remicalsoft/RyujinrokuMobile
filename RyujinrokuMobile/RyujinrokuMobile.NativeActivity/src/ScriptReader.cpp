#include "ScriptReader.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"

ScriptReader::ScriptReader(){}
ScriptReader::~ScriptReader(){}

char *levelName[eLevel_Num] = {
	"easy_",
	"normal_",
	"hard_",
};

std::vector<Script>* ScriptReader::read(int level, int stage){

	std::vector<Script>* script = new std::vector<Script>;

	int lineNum, num, i, fp;
	char fileName[256];
	int input[64];
	char inputStr[64];

	sprintf(fileName, "dat/script/%s%d.csv", levelName[level], stage);

	fp = FileRead_open(fileName);
	if (fp == 0) {
		printfDx("script load error\n");
		return nullptr;
	}
	for (i = 0; i < 2; i++) {//最初の2行読み飛ばす
		while (FileRead_getc(fp) != '\n');
	}

	lineNum = 0, num = 0;
	Script s;
	while (1) {
		for (i = 0; i<64; i++) {
			inputStr[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (input[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputStr[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		switch (num) {
		case  0: s.count		= atoi(inputStr); break;
		case  1: s.moveType		= atoi(inputStr); break;
		case  2: s.enemyType	= atoi(inputStr); break;
		case  3: s.x			= atof(inputStr); break;
		case  4: s.xrand		= atof(inputStr); break;
		case  5: s.y			= atof(inputStr); break;
		case  6: s.yrand		= atof(inputStr); break;
		case  7: s.speed		= atof(inputStr); break;
		case  8: s.startTime	= atoi(inputStr); break;
		case  9: s.barrageType	= atoi(inputStr); break;
		case 10: s.bulletColor	= atoi(inputStr); break;
		case 11: s.bulletType	= atoi(inputStr); break;
		case 12: s.hp			= atoi(inputStr); break;
		case 13: s.waitTime		= atoi(inputStr); break;
		case 14: s.itemType		= atoi(inputStr); break;
		}
		num++;
		if (num == 15) {
			s.xrand = randf2(s.xrand);
			s.yrand = randf2(s.yrand);
			script->push_back(s);
			num = 0;
			lineNum++;
		}
	}
EXFILE:
	FileRead_close(fp);

	return script;
}
