#pragma once

class ISpellcardDisablable
{
public:
	ISpellcardDisablable();
	~ISpellcardDisablable();
	virtual void disableSpellcardGettable() = 0;
};

