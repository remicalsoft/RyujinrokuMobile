#pragma once

class PlayerLaserFactor {
	int img;
	float x, y, size;
public:
	PlayerLaserFactor(float y);
	void update();
	void draw(float sx, float sy);
};
