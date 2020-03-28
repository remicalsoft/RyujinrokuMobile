#pragma once

#include "Task.h"
#include "Replayer.h"

class ReplayCell :
	public Task
{
	int _x, _y, _id;
	int _font;
	int _img, _imgSelected;
	bool _isActivated;
	ReplayHeader* _header;
	char _fileName[128];
public:
	ReplayCell(int x, int y, int id, int img, int imgSelected, int font);
	~ReplayCell();
	bool update() override;
	void draw() override;
	void enable() {
		_isActivated = true;
	}
	void disable() {
		_isActivated = false;
	}
	bool isAvailable() {
		return !(_header == nullptr);
	}
	ReplayHeader* getReplayHeader() {
		return _header;
	}
	char* getFileName() {
		return _fileName;
	}
};

