#pragma once

enum eShakeType {
	eShakeType_BOMB,
	eShakeType_BOSS_DEAD,
	eShakeType_BOSS_LAST_DEAD,
};

class IShakeListener {
public:
	virtual void onShake(eShakeType type) = 0;
};