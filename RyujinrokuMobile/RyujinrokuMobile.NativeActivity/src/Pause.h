#pragma once

#include "Task.h"
#include <vector>
#include "LevelItem.h"
#include "ISceneChangedListener.h"
#include "IResetChapterListener.h"
#include "ChapterData.h"

class Pause {
	enum ePauseGraphic {
		ePauseGraphic_RetryLastChapter,		//チャプターをやりなおす
		ePauseGraphic_BackToTitle,			//タイトルに戻る
		ePauseGraphic_BackToGame,			//ゲームに戻る
		ePauseGraphic_RetryStart,			//スタートからやり直す
		ePauseGraphic_BackToTitleEX,			//タイトルに戻る
		ePauseGraphicNum,
	};

	enum ePauseSelect {
		ePauseSelect_BackToGame,
		ePauseSelect_BackToTitle,
		ePauseSelect_RetryStart,
		ePauseSelect_Num,
	};

	enum eDiedPauseSelect {
		eDiedPauseSelect_RetryLastChapter,		//チャプターをやりなおす
		eDiedPauseSelect_BackToTitle,			//タイトルに戻る
		eDiedPauseSelect_RetryStart,			//スタートからやり直す
		eDiedPauseSelect_Num,
	};

	int _imgs[ePauseGraphicNum];
	bool _isPause;
	bool _isPractice;
	bool _isSpellPractice;
	bool _isPlayerDied;
	int _selectID;
	bool _isFinalized, _isCanceled;
	int _counter, _finalizeCounter, _cancelCounter;
	int _startTime;
	std::vector<LevelItem*> _items;
	ISceneChangedListener *_implSceneChanger;
	IResetChapterListener *_implResetChapter;

public:
	Pause(bool isPractice, bool isSpellPractice, ISceneChangedListener*, IResetChapterListener*);
	~Pause();
	bool isPause() {
		return _isPause;
	}
	bool update(ChapterData* chapterData);
	void draw();
	void onPlayerDied();
};

