#include "TotalPlayTime.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "SavedData.h"

const static int NO_PRESS_TIME = 2 * 60 * 1000;

TotalPlayTime::TotalPlayTime()
{
	_noPressCounter = 0;
	_font = CreateFontToHandle(FONT, 17, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

TotalPlayTime::~TotalPlayTime()
{
}

void TotalPlayTime::update()
{
	for (int i = 0; i < PAD_TYPE_NUM; i++) {
		if (Pad::getIns()->get((ePad)i) > 0) {
			_noPressCounter = 0;
		}
	}
	_noPressCounter++;
	if (_noPressCounter < NO_PRESS_TIME) {
		SavedData::getIns()->dat.totalPlayTime++;
	}
}

void TotalPlayTime::draw(int x, int y)
{
	int time = SavedData::getIns()->dat.totalPlayTime;
	DrawFormatStringToHandle(x, y, GetColor(255,255,255), _font, "総プレイ時間 %02d:%02d", time/60/60/60, (time/60/60)%60);
}
