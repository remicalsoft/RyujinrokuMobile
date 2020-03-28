#include "MenuSelectUtils.h"
#include "DebugMode.h"
#include "Keyboard.h"
#include "SavedData.h"
#include <DxLib.h>
#include "Define.h"

MenuSelectUtils::MenuSelectUtils()
{
}


MenuSelectUtils::~MenuSelectUtils()
{
}

bool MenuSelectUtils::canSelectPracticeStage(int level, int stage) {
	if (SavedData::getIns()->dat.isClearStage[level][stage - 1]) {
		return true;
	}
	if (DebugMode::getIns()->isON) {
		return true;
	}
	return false;
}

bool MenuSelectUtils::canSelectEXStage(int level)
{
	if (SavedData::getIns()->dat.isClearStage[level][eStage5]) {
		return true;
	}
	if (DebugMode::getIns()->isON) {
		return true;
	}
	return false;

}
bool MenuSelectUtils::canSelectPHStage(int level)
{
	if (SavedData::getIns()->dat.isClearStage[level][eStageEX]) {
		return true;
	}
	if (DebugMode::getIns()->isON) {
		return true;
	}
	return false;
}

bool MenuSelectUtils::isClearStage(int stage)
{
	if (SavedData::getIns()->dat.isClearStage[eLevel_Easy][stage]) {
		return true;
	}
	if (SavedData::getIns()->dat.isClearStage[eLevel_Normal][stage]) {
		return true;
	}
	if (SavedData::getIns()->dat.isClearStage[eLevel_Hard][stage]) {
		return true;
	}
	if (DebugMode::getIns()->isON) {
		return true;
	}
	return false;
}

bool MenuSelectUtils::havePlayed(int stage)
{
	if (SavedData::getIns()->dat.havePlayed[stage]) {
		return true;
	}
	if (DebugMode::getIns()->isON) {
		return true;
	}
	return false;
}
