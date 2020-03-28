#include "SE.h"
#include <DxLib.h>

int SE::myLoadSound(char *fileName)
{
	int ret = LoadSoundMem(fileName);
	ChangeVolumeSoundMem(volume * 255 / 100, ret);
	_se.push_back(ret);
	reset();
	return ret;
}

SE::SE(){
	volume = 0;
}

SE::~SE()
{
	for (auto se : _se) {
		DeleteSoundMem(se);
	}
}

void SE::load(int volume) {
	this->volume = volume;
	seHandle[eSE_upDown] = myLoadSound("dat/sound/menu/updown.wav");
	seHandle[eSE_hit] = myLoadSound("dat/sound/game/hit.wav");
	seHandle[eSE_hitFinal] = myLoadSound("dat/sound/game/hitFinal.wav");
	seHandle[eSE_disappear] = myLoadSound("dat/sound/game/disappear.wav");
	seHandle[eSE_enemyShot] = myLoadSound("dat/sound/game/enemyShot.wav");
	seHandle[eSE_enemyShotSmall] = myLoadSound("dat/sound/game/enemyShotSmall.wav");
	seHandle[eSE_laser] = myLoadSound("dat/sound/game/laser.wav");
	seHandle[eSE_getItem] = myLoadSound("dat/sound/game/getItem.wav");
	seHandle[eSE_playerShot] = myLoadSound("dat/sound/game/playerShot.wav");
	seHandle[eSE_playerDead] = myLoadSound("dat/sound/game/playerDead.wav");
	seHandle[eSE_dieBoss] = myLoadSound("dat/sound/game/dieBoss.wav");
	seHandle[eSE_spell] = myLoadSound("dat/sound/game/spell.wav");
	seHandle[eSE_theLast] = myLoadSound("dat/sound/game/theLast.wav");
	seHandle[eSE_hanabiShot] = myLoadSound("dat/sound/game/hanabiShot.wav");
	seHandle[eSE_hanabiExplosion] = myLoadSound("dat/sound/game/hanabiExplosion.wav");
	seHandle[eSE_hanabiFukidashi] = myLoadSound("dat/sound/game/hanabiFukidashi.wav");
	seHandle[eSE_hanabiFukidashi2] = myLoadSound("dat/sound/game/hanabiFukidashi.wav");
	seHandle[eSE_freeze] = myLoadSound("dat/sound/game/freeze.wav");
	seHandle[eSE_rain] = myLoadSound("dat/sound/game/rain.wav");
	seHandle[eSE_rainbow] = myLoadSound("dat/sound/game/rainbow.wav");
	seHandle[eSE_bom] = myLoadSound("dat/sound/game/bom.wav");
	seHandle[eSE_getSpellcard] = myLoadSound("dat/sound/game/スペルカード取得.wav");
	seHandle[eSE_odamaCollision] = myLoadSound("dat/sound/game/大弾ぶつかり.wav");
	seHandle[eSE_selectDetail] = myLoadSound("dat/sound/menu/selectDetail.wav");
	seHandle[eSE_select] = myLoadSound("dat/sound/menu/select.wav");
	seHandle[eSE_cancel] = myLoadSound("dat/sound/menu/cancel.wav");
	seHandle[eSE_error] = myLoadSound("dat/sound/menu/error.wav");
	seHandle[eSE_bought] = myLoadSound("dat/sound/menu/bought.wav");
	seHandle[eSE_page] = myLoadSound("dat/sound/op/page.wav");
	seHandle[eSE_graze] = myLoadSound("dat/sound/game/graze.wav");
	seHandle[eSE_countDown] = myLoadSound("dat/sound/game/time.wav");
	seHandle[eSE_dress] = myLoadSound("dat/sound/game/dress.wav");
	seHandle[eSE_equip] = myLoadSound("dat/sound/menu/equip.wav");
}
