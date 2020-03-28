#include "GameEnding.h"
#include <DxLib.h>
#include "Define.h"

GameEnding::GameEnding()
{
	_isAvailable = false;
	_bright = 0;
}


GameEnding::~GameEnding()
{
}

bool GameEnding::update()
{
	if(!_isAvailable)
	{
		return true;
	}

	_bright += 2;
	if (_bright > 255) {
		return false;
	}
	return true;
}

void GameEnding::draw()
{
	if (!_isAvailable) {
		return;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _bright);
	DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
