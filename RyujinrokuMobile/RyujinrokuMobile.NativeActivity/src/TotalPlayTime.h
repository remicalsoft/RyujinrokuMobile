#pragma once
#include "Singleton.h"
class TotalPlayTime :
	public Singleton<TotalPlayTime>
{
	int _font;
	int _noPressCounter;
public:
	TotalPlayTime();
	~TotalPlayTime();
	void update();
	void draw(int x, int y);
};

