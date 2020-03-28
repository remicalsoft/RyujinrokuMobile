#pragma once

#include "Background.h"

class BackgroundFactory
{
public:
	BackgroundFactory();
	~BackgroundFactory();
	static void create(int stage, Background **background, Background **backgroundSpell);
};

