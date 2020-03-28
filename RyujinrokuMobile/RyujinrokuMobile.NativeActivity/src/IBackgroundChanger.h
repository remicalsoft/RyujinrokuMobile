#pragma once

class IBackgroundChanger {
public:
	virtual void changeBackground(bool isSpell, bool isFinal) = 0;
};