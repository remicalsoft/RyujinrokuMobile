#include "GetSpellcardEffect.h"
#include "SE.h"
#include "Define.h"
#include "Image.h"

GetSpellcardEffect::GetSpellcardEffect(int spellcardbonus, int type)
{
	_type = type;
	_counter = 0;
	_bonusScore = spellcardbonus;
	_font = CreateFontToHandle(FONT, 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}


GetSpellcardEffect::~GetSpellcardEffect()
{
	DeleteFontToHandle(_font);
}

bool GetSpellcardEffect::update()
{
	_counter++;
	if (_counter==1) {
		SE::getIns()->setPlay(eSE_getSpellcard);
	}
	if (_counter == 80 + 32) {
		return false;
	}
	return true;
}

void GetSpellcardEffect::draw()
{
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	if (_counter<20) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256/20.f*_counter);
		DrawRotaGraphF(CENTER_X,CENTER_Y,0.5+0.5/20*_counter,0.0,Image::getIns()->getSpellcard[_type],TRUE);
	}
	else {
		if (80 < _counter && _counter < 80 + 32) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256- 256/32.f*(_counter-80));
		}
		DrawRotaGraphF(CENTER_X, CENTER_Y, 1.0 + 0.2 / 100 * (_counter-20), 0.0, Image::getIns()->getSpellcard[_type], TRUE);
	}
	int w = GetDrawFormatStringWidthToHandle(_font, "BONUS %d", _bonusScore);
	DrawFormatStringToHandle(CENTER_X - w/2, CENTER_Y + 200, GetColor(255, 255, 255), _font, "BONUS %d",_bonusScore);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	if (20 < _counter&&_counter < 80 + 32) {
		if (80 < _counter && _counter < 80 + 32) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256 - 256 / 32.f*(_counter - 80));
		}
		DrawRotaGraphF(CENTER_X, CENTER_Y, 1.0 + 0.1 / 100 * (_counter - 20), 0.0, Image::getIns()->getSpellcardFont, TRUE);
	}
	if (20<_counter && _counter<60) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - 255 / 40.f*(_counter-20));
		for (int i = 0; i < 5; i++) {
			DrawRotaGraphF(CENTER_X, CENTER_Y, 1.0 + 0.5 / 100 * (_counter - 20)*i, 0.0, Image::getIns()->getSpellcardFont, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawMode(DX_DRAWMODE_NEAREST);
}
