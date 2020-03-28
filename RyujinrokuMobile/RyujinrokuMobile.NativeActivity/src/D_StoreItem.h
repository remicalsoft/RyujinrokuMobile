#pragma once
class D_StoreItem
{
public:
	const char* name;
	const char* explanation;
	int price;
	D_StoreItem(const char* name, const char* explanation, int price) {
		this->name = name;
		this->explanation = explanation;
		this->price = price;
	}
};

