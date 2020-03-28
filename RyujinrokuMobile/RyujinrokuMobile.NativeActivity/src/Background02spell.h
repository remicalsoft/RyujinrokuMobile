#pragma once

#include "SrfMgr05.h"
#include "Background.h"

class Background02spell : public Background
{
	class Srf {
	public:
		float x, y;
		int img;
		Srf(float x, float y, int img) {
			this->x   = x;
			this->y   = y;
			this->img = img;
		}
	};
	int _img[2];
	const static int NUM = 4;
	Srf* _srf[NUM];
public:
	Background02spell();
	~Background02spell();
	bool update() override;
	void draw() override;
};

