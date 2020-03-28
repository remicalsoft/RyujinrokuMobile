#pragma once

#include "Task.h"
#include <DxLib.h>

class TalkBase :
	public Task
{
protected:
	const int X =64;
	const int INIT_X =300;
	int _img;
	int _counter;
	float _x, _initX;
	int _bright;
	bool _isEnabled;
	bool _isAvailable;
	bool _isAppeared;
public:
	TalkBase() {
		_img = 0;
		_counter = 0;
		_x = 0;
		_bright = 64;
		_isEnabled = false;
		_isAvailable = false;
		_isAppeared = false;
	}
	bool isAppeared() {
		return _isAppeared;
	}
	bool isEnabled() {
		return _isEnabled;
	}
	void set(int img) {
		_img = img;
	}
	void enable() {
		if (!_isEnabled) {
			_isEnabled = true;
		}
		_isAppeared = true;
	}
	void disable() {
		if (_isEnabled) {
			_isEnabled = false;
		}
	}
	void setIsAvailable(bool isAvailable) {
		_isAvailable = isAvailable;
		_counter = 0;
		_x = 0;
		_bright = 64;
	}
};

