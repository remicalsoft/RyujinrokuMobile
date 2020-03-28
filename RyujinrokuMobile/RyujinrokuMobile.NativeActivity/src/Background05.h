#pragma once

#include "SrfMgr05.h"
#include "Background.h"

class Background05 : public Background
{
	SrfMgr05* _srfMgr;
public:
	Background05();
	~Background05();
	bool update() override;
	void draw() override;
};

