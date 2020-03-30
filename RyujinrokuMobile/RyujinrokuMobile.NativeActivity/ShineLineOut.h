#pragma once

#include "ShineLine.h"

class ShineLineOut : public ShineLine {
	bool isNear();
public:
	ShineLineOut(float x, float y);
	bool update() override;
};