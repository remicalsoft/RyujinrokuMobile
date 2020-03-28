#include "MusicSelectUtils.h"
#include "DebugMode.h"
#include "Keyboard.h"
#include "SavedData.h"
#include <DxLib.h>
#include "Define.h"

MusicSelectUtil::MusicSelectUtil() {

}

MusicSelectUtil::~MusicSelectUtil() {

}

bool MusicSelectUtil::canPlayMusic(int id) {
	if (SavedData::getIns()->dat.havePlayedMusic[id]) {
		return true;
	}
	if (DebugMode::getIns()->isON) {
		return true;
	}
	return false;
}