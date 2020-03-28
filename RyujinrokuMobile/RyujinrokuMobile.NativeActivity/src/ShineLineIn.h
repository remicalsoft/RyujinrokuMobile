#pragma once

#include "ShineLine.h"

#define SHINE_X 863
#define SHINE_Y 308
#define SHINE_R 10

class ShineLineIn : public ShineLine {
public:
	ShineLineIn(float x, float y);
	bool update() override;
};