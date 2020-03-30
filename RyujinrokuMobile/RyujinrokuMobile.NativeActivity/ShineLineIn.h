#pragma once

#include "ShineLine.h"

#define SHINE_X 791
#define SHINE_Y 475
#define SHINE_R 10

class ShineLineIn : public ShineLine {
public:
	ShineLineIn(float x, float y);
	bool update() override;
};