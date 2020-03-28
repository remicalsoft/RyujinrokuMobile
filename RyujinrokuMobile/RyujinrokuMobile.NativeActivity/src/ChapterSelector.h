#pragma once

#include "Task.h"
#include "LevelItem.h"
#include <vector>

class ChapterSelector
	: public Task
{
	int selectChapter[3];
	std::vector<LevelItem> _itemList;
	bool _isYes;
	bool _isDecided;
public:
	ChapterSelector();
	~ChapterSelector();
	bool update() override;
	void draw() override;
	static bool exists();

	bool isDecided() {
		return _isDecided;
	}
};

