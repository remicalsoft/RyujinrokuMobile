#pragma once

#include "Singleton.h"

class GameCounter : public Singleton<GameCounter> {
	int _n;
	bool _isLocked;

public:
	GameCounter();
	~GameCounter();
	void update();
	int get();
	void lock();
	void unlock();
	void initialize();
	void increment() {
		_n++;
	}
	void set(int cnt);
};

