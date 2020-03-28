#pragma once
class SpellcardWatcher
{
	bool _isAvailable;
public:
	SpellcardWatcher();
	~SpellcardWatcher();
	void clear() {
		_isAvailable = true;
	}
	void disable() {
		_isAvailable = false;
	}
	bool get() {
		return _isAvailable;
	}
};

