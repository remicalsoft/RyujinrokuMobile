#pragma once

class pt_t {
public:
	float x, y;
	pt_t() {
		x = y = 0;
	};
	pt_t(float x, float y) {
		this->x = x;
		this->y = y;
	}
};
