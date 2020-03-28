#pragma once

#include "ScenePrmBase.h"
#include "Define.h"

class ShoScenePrm :
	public ScenePrmBase
{
public:
	eStage _eStage;
	ShoScenePrm();
	~ShoScenePrm();
};

