#pragma once

#include "Task.h"

enum EMusic{eMenu, eEndroll, eSt1, eSt1Boss, eSt2, eSt2Boss,  eSt3, eSt3Boss,  eSt4, eSt4Boss,  eSt5, eSt5Boss,  eStEX, eStEXBoss,  eStPh, eStPhBoss,};

class MusicMgr : public Task
{
	int _stage;
	int _bgm;
	int _bgmSP;
	int _counter;
	bool _isBoss;
	int _font;
	int _bossPlayedN;
	float _x, _y, _v, _a;
	const char* _title;
public:
	MusicMgr(int stage);
	~MusicMgr();
	void stop();
	bool isPlaying();
	void setBossPlayedN(int n);
	int getBossPlayedN() {
		return _bossPlayedN;
	}
	void play(bool isBoss);
	void playSP();
	bool update() override;
	void draw() override;
};

