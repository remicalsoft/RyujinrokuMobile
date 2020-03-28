#pragma once
#include "Singleton.h"

class CommonStatus : public Singleton<CommonStatus> {
	int pad[PAD_MAX];
public:
	Pad();
	~Pad();
	void update();
	int get(ePad eID);
};


