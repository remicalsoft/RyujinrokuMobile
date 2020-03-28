#pragma once

#include "ScenePrmBase.h"
#include "Define.h"

class GameScenePrm :
	public ScenePrmBase
{
public:
	eStage _stage;
	eLevel _level;
	bool _isFromPractice;
	int _spellPracticeSpellID;

	eStage getStage();
	eLevel getLevel();
	GameScenePrm();
	GameScenePrm(eStage stage, eLevel level);
	~GameScenePrm();
};

