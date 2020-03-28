#pragma once
#include "ScenePrmBase.h"
class MenuScenePrm :
	public ScenePrmBase
{
	int _bgmHandle;
public:
	MenuScenePrm() {
		_bgmHandle = -1;
	}
	void setBgmHandle(int handle) {
		_bgmHandle = handle;
	}
	int getBgmHandle() {
		return _bgmHandle;
	}
};

