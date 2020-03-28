#pragma once

#include "Singleton.h"


class DebugMode : public Singleton<DebugMode>
{
public:
	bool isUnlocked;
	bool isON;
	bool isPlayerInvincible;
	DebugMode();
	~DebugMode();
	int switchStage();
	void update();
};

