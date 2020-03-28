#pragma once

class IResetChapterListener {
public:
	virtual void onResetChapter() = 0;
	virtual void onCreateChapter() = 0;
};