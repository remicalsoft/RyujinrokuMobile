#include "Time.h"
#include <DxLib.h>
#include "Define.h"
#include "SE.h"

Time::Time()
{
	LoadDivGraph("dat/image/number/number.png", 10, 10, 1, 32, 36, _img);
}

Time::~Time()
{
	for (int i = 0; i < 10; i++) {
		DeleteGraph(_img[i]);
	}
}

bool Time::update()
{
	_frame--;
	if (_frame < 0) {
		_frame = 0;
	}
	if (_frame <= 7 * 60) {
		if (_frame % 60 == 0) {
			SE::getIns()->setPlay(eSE_countDown);
		}
	}
	return false;
}

void Time::draw()
{
	int frame = _frame;
	if (frame > 99 * 60) {
		frame = 99 * 60;
	}
	int time = frame / 60;
	DrawGraph(OUT_W - 64 - 32 - 32, 6, _img[(time / 10)%10], TRUE);
	DrawGraph(OUT_W - 64 - 32,      6, _img[time % 10], TRUE);
}

void Time::setTime(int frame)
{
	_frame = frame;
}

int Time::getTime() {
	return _frame;
}

bool Time::isTimeOver()
{
	return _frame==0;
}
