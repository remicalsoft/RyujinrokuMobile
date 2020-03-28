#pragma once

#include "SrfMgr05.h"
#include "Background.h"

class BackgroundPH : public Background
{
	SrfMgr05* _srfMgr;
public:
	BackgroundPH();
	~BackgroundPH();
	bool update() override;
	void draw() override;
};

