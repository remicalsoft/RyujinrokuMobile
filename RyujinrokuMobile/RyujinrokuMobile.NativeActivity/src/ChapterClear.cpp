#include "ChapterClear.h"
#include <DxLib.h>
#include "Define.h"
#include "GameCounter.h"
#include "GameData.h"
#include "Utils.h"
#include "Keyboard.h"

using namespace std;

const static int N = 3;
const static int Wait = 50;
const static int FINISH_COUNT = 200;

ChapterClear::ChapterClear(Boss* boss)
{
	_imgAutoSaving = LoadGraph("dat/image/else/autoSaving.png");
	_imgClear      = LoadGraph("dat/image/else/chapterClear.png");
	_counter = FINISH_COUNT;
	_boss = boss;
	_a = 0;
}


ChapterClear::~ChapterClear()
{
	DeleteGraph(_imgAutoSaving);
	DeleteGraph(_imgClear);
}

bool ChapterClear::update()
{
	int stage = GameData::getIns()->stage;
	const int* cnt = _boss->getSaveCount();
	for (int i = 0; i < N; i++) {
		if (cnt[i]-150 == GameCounter::getIns()->get()) {
			_counter = 0;
		}
	}

	_counter++;

	//点滅処理
	if (35 <= _counter && _counter < 35 + 120) {
		_a = 128 + GetRand(128);
	}

	return true;
}

void ChapterClear::draw()
{
	if(0 <= _counter && _counter < 35 + 120 + 35)
	{
		if (0 <= _counter && _counter < 35) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128*_counter/35);
		}
		if (35 <= _counter && _counter < 35 + 120) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _a);
		}
		if (35 + 120 <= _counter && _counter < 35 + 120 + 35) {
			int c = 35 + 120;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128 - 128*(_counter-c)/35);
		}

		DrawRotaGraphF(CENTER_X, 150, 1.0, 0.0, _imgAutoSaving, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (0 <= _counter && _counter<32) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 100 * _counter / 32);
		}
		else if (120 <= _counter && _counter<120 + 70) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 100 - 100 * (_counter - 120) / 70);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
		}
		for (int i = 1; i <= 3; i++) {
			float subX = Utils::getSinValue_90(_counter / 30., -200 * i / 3);
			DrawRotaGraphF(CENTER_X + 200*i/3 + subX, 200, 1.0, 0.0, _imgClear, TRUE);
			subX = Utils::getSinValue_90(_counter / 30., +200 * i / 3);
			DrawRotaGraphF(CENTER_X - 200*i/3 + subX, 200, 1.0, 0.0, _imgClear, TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

bool ChapterClear::isChapterFinished()
{
	const int* cnt = _boss->getSaveCount();
	if (cnt == NULL) {
		return false;
	}
	for (int i = 0; i < N; i++) {
		if (cnt[i]-150-50 == GameCounter::getIns()->get()) {
			return true;
		}
	}
	return false;
}
