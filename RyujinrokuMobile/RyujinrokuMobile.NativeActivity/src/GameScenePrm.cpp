#include "GameScenePrm.h"

GameScenePrm::GameScenePrm(eStage stage, eLevel level)
{
	_stage = stage;
	_level = level;
	_isFromPractice = false;
	_spellPracticeSpellID = -1;
}

GameScenePrm::~GameScenePrm()
{
}

eStage GameScenePrm::getStage()
{
	return _stage;
}

eLevel GameScenePrm::getLevel()
{
	return _level;
}

GameScenePrm::GameScenePrm()
{
}
