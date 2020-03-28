#include <DxLib.h>
#include "Background01spell.h"
#include "Define.h"

const static int H = 879;

Background01spell::Background01spell(){
	_img[0] = LoadGraph("dat/image/background/01spell/00.png");
	_img[1] = LoadGraph("dat/image/background/01spell/01.png");
	for (int i = 0; i < NUM; i++) {
		_srf[i] = new Srf(0,H*i,_img[i%2]);
	}
}

Background01spell::~Background01spell(){
	for (int i = 0; i < NUM; i++) {
		delete _srf[i];
	}
}

bool Background01spell::update(){
	Background::update();
	for (int i = 0; i < NUM; i++) {
		_srf[i]->y-=2;
		if (_srf[i]->y < -H) {
			_srf[i]->y += H * 4;
		}
	}
	return true;
}

void Background01spell::draw(){
	SetDrawArea(0, 0, OUT_W, OUT_H);
	for (int i = 0; i < NUM; i++) {
		DrawGraphF(_srf[i]->x + offset.x, _srf[i]->y + offset.y, _srf[i]->img,FALSE);
	}
	SetDrawArea(0, 0, WIN_W, WIN_H);
}
