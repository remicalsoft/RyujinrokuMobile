#pragma once

class ITalkStatusGettable {
public:
	virtual ~ITalkStatusGettable() {}
	virtual bool isNowTalking() = 0;
};