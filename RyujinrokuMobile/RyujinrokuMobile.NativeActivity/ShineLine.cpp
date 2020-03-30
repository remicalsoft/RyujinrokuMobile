#include "ShineLine.h"
#include <DxLib.h>

void ShineLine::draw() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawBlendMode(DX_BLENDMODE_ADD, _alfa);
	DrawLineAA((int)_x1, (int)_y1, (int)_x2, (int)_y2, _color);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
