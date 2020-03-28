#pragma once

#include "Task.h"
#include <vector>
#include "TalkAisha.h"
#include "TalkEnemy.h"
#include "GameEnding.h"
#include "MusicMgr.h"
#include "Boss.h"

class Boss;

class TalkMgr : public Task
{

	TalkEnemy _talkEnemy;

protected:
	int  _stage;
	int  _n;
	int  _font;
	int  _charN;
	int  _counter;
	bool _isAvailable;
	bool _isEnd;
	int _imgBackAisha, _imgBackEnemy;
	std::vector<int> _aisha;
	std::vector<int> _enemy;
	TalkAisha _talkAisha;
	GameEnding *_gameEnding;
	MusicMgr *_musicMgr;
	Boss* _boss;

public:
	TalkMgr(GameEnding* _gameEnding, MusicMgr *musicMgr, Boss* boss);
	~TalkMgr();
	void set();
	bool update() override;
	void draw() override;
	bool isAvailable() {
		return _isAvailable;
	}
	virtual int getCutInImage();
	virtual void enable();
	void skip();
};
