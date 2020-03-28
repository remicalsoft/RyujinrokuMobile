#pragma once
#include "Task.h"
class GetSpellcardEffect :
	public Task
{
	int _counter;
	int _bonusScore;
	int _font;
	int _type;
public:
	GetSpellcardEffect(int spellcardbonus, int type);
	~GetSpellcardEffect();
	bool update() override;
	void draw() override;
};

