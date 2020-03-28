#pragma once

#include "TalkMgr.h"

class TalkMgrEX : public TalkMgr
{
	std::vector<int> _yohi;
	std::vector<int> _toko;
	std::vector<int> _yuyumi;
	std::vector<int> _dakki;

	TalkEnemy _talkYohi;
	TalkEnemy _talkToko;
	TalkEnemy _talkYuyumi;
	TalkEnemy _talkDakki;

	void disableAll();

public:
	TalkMgrEX(GameEnding* _gameEnding, MusicMgr *musicMgr, Boss* boss);
	~TalkMgrEX();
	bool update() override;
	void draw() override;

	void set();
	int getCutInImage();
	void enable();
};
