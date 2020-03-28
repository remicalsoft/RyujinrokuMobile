#include <DxLib.h>
#include "ChapterSelector.h"
#include "Define.h"
#include "Pad.h"
#include "SE.h"

ChapterSelector::ChapterSelector()
{
	LoadDivGraph("dat/image/menu/selectChapter.png", 3, 1, 3, 437, 40, selectChapter);
	for (int i = 0; i < 3; i++) {
		_itemList.push_back(LevelItem(WIN_W / 2, WIN_H / 2 - 20, selectChapter[1], true));
		_itemList.push_back(LevelItem(WIN_W / 2, WIN_H / 2 + 20, selectChapter[2], false));
	}
	_isYes = true;
	_isDecided = true;
}

ChapterSelector::~ChapterSelector()
{
	for (int i = 0; i < 3; i++) {
		DeleteGraph(selectChapter[i]);
	}
}

bool ChapterSelector::update()
{

}

void ChapterSelector::draw()
{

}

bool ChapterSelector::exists()
{

}
