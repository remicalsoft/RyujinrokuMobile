#pragma once

#include "Singleton.h"
#include <DxLib.h>

class BGM : public Singleton<BGM>
{
	int menu;
	int volume;
public:
	BGM() {
		menu = 0;
		volume = 0;
	}
	~BGM() {}
	void startMenuBGM() {
		#define LOOPPOS_MENU 19459
		if (menu == 0) {
			menu = LoadSoundMem("dat/bgm/menu/bgm.ogg");
			ChangeVolumeSoundMem(volume * 255 / 100, menu);
			SetLoopPosSoundMem(LOOPPOS_MENU, menu);
			PlaySoundMem(menu, DX_PLAYTYPE_LOOP);
		}
		else {
			if (CheckSoundMem(menu) == 0) {
				SetLoopPosSoundMem(LOOPPOS_MENU, menu);
				PlaySoundMem(menu, DX_PLAYTYPE_LOOP);
			}
		}

	}
	void stopMenuBGM() {
		StopSoundMem(menu);
	}
	void deleteMenuBGM() {
		DeleteSoundMem(menu);
		menu = 0;
	}
	void setVolume(int volume) {
		this->volume = volume;
	}
	int getVolume() {
		return volume;
	}
};

