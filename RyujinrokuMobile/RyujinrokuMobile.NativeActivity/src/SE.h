#pragma once
#include "Singleton.h"
#include <vector>
#include <string.h>
#include <DxLib.h>

enum eSE {
	eSE_hit,
	eSE_hitFinal,
	eSE_disappear,
	eSE_enemyShot,
	eSE_enemyShotSmall,
	eSE_laser,
	eSE_getItem,
	eSE_playerShot,
	eSE_playerDead,
	eSE_dieBoss,
	eSE_spell,
	eSE_theLast,
	eSE_hanabiShot,
	eSE_hanabiExplosion,
	eSE_hanabiFukidashi,
	eSE_hanabiFukidashi2,
	eSE_freeze,
	eSE_rain,
	eSE_rainbow,
	eSE_bom,
	eSE_getSpellcard,
	eSE_odamaCollision,
	eSE_selectDetail,
	eSE_select,
	eSE_cancel,
	eSE_error,
	eSE_bought,
	eSE_page,
	eSE_upDown,
	eSE_graze,
	eSE_countDown,
	eSE_dress,
	eSE_equip,

	eSE_NUM,
};

class SE : public Singleton<SE>{

	std::vector<int> _se;

	int myLoadSound(char*);
	int  seHandle[eSE_NUM];
	bool playFlag[eSE_NUM];
	int volume;

public:

	SE();
	~SE();
	void load(int volume);
	void reset() {
		memset(playFlag, 0, sizeof(playFlag));
	}
	void setPlay(eSE id) {
		playFlag[id] = true;
	}
	void stopPlay(eSE id) {
		StopSoundMem(seHandle[id]);
	}
	void play() {
		for (int i = 0; i < eSE_NUM; i++) {
			if (playFlag[i]) {
				PlaySoundMem(seHandle[i], DX_PLAYTYPE_BACK);
			}
		}
		reset();
	}
};

