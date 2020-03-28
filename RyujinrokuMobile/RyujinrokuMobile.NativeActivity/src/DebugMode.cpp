#include "DebugMode.h"
#include <DxLib.h>
#include "Keyboard.h"
#include "GameData.h"
#include "Toast.h"
#include "SE.h"
#include <DxLib.h>

DebugMode::DebugMode()
{
	isON = false;
	isPlayerInvincible = false;
	isUnlocked = false;
}

DebugMode::~DebugMode()
{
}

int DebugMode::switchStage() {
	if (DebugMode::getIns()->isON) {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_1)) {
			GameData::getIns()->stage = 0;
			return 0;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_2)) {
			GameData::getIns()->stage = 1;
			GameData::getIns()->power = 100;
			return 1;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_3)) {
			GameData::getIns()->stage = 2;
			GameData::getIns()->power = 200;
			return 2;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_4)) {
			GameData::getIns()->stage = 3;
			GameData::getIns()->power = 300;
			return 3;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_5)) {
			GameData::getIns()->stage = 4;
			GameData::getIns()->power = 400;
			return 4;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_6)) {
			GameData::getIns()->stage = 5;
			return 5;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_7)) {
			GameData::getIns()->stage = 6;
			return 6;
		}
	}
	return -1;
}

void DebugMode::update() 
{	//ついでにデバッグコマンド
	if (isUnlocked && Keyboard::getIns()->getPressingCount(KEY_INPUT_D) == 1)
	{
		isON = !isON;
		string str = "デバックモードが";
		str += ((isON == true) ? "有効" : "無効");
		str += "になりました。";
		Toast::getIns()->add(str.c_str());
	}
	if (isON)
	{
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_1) == 1)
		{
			isPlayerInvincible = !isPlayerInvincible;
			string str = "無敵モードが";
			str += ((isPlayerInvincible == true) ? "有効" : "無効");
			str += "になりました。";
			Toast::getIns()->add(str.c_str());
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_M) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_M) > 30)
		{
			GameData::getIns()->setMoney(GameData::getIns()->getMoney()+100);
			SE::getIns()->setPlay(eSE::eSE_bought);
		}
	}
}
