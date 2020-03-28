#pragma once

#include "Task.h"
#include "Player.h"
#include "Item.h"
#include <list>

class ItemMgr :
	public Task
{

	Player *_player;
	std::list<Item*> _itemList;

public:
	ItemMgr(Player *player);
	~ItemMgr();
	bool update() override;
	void draw() override;
	void regist(float x, float y, eItemPopType type);

};

