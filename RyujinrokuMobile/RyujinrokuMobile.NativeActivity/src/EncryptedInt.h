#pragma once
class EncryptedInt
{
	int* value;
	int hashValue;
public:
	EncryptedInt();
	~EncryptedInt();
	bool isTampered();
	void set(int value);
	int  get();
};

