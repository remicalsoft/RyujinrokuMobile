#include "EndrollImage.h"
#include <DxLib.h>
#include "Define.h"

const static int FIRST = 200;
const static int KEEP = 120;
const static int END = 190;

EndrollImage::EndrollImage(char* imgPath, bool isEnd)
{
	_img = LoadGraph(imgPath);
	_counter = 0;
	_isEnd = isEnd;
}


EndrollImage::~EndrollImage()
{
	DeleteGraph(_img);
}

bool EndrollImage::update()
{
	_counter++;
	if (_counter == FIRST + KEEP + END) {
		return false;
	}
	return true;
}

void EndrollImage::draw()
{
	if (_counter<FIRST) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _counter*256/FIRST);
	}
	if (FIRST + KEEP<_counter && _counter<FIRST + KEEP + END) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (_counter - (FIRST + KEEP)) * (255.f/END));
	}
	if (_isEnd) {
		DrawGraph(WIN_W/2-138/2, WIN_H/2-34/2, _img, TRUE);
	}
	else {
		DrawGraph(WIN_W - 660, WIN_H - 600, _img, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
