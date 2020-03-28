#pragma once
#include "Task.h"
#include <DxLib.h>
#include <list>
#include "Define.h"
#include "Boss.h"

class ChapterClear :
	public Task
{
	int _imgClear;
	int _imgAutoSaving;
	int _counter;
	int _a;
	Boss* _boss;

public:
	ChapterClear(Boss* boss);
	~ChapterClear();
	bool update() override;
	void draw() override;

	bool isChapterFinished();
};

