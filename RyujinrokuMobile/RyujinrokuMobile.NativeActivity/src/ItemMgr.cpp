#include "ItemMgr.h"
#include "Utils.h"
#include "GameData.h"
#include "Pad.h"
#include "SE.h"
#include "SavedData.h"
#include "StoreBuyScene.h"
#include "Replayer.h"

using namespace std;

ItemMgr::ItemMgr(Player* player)
{
	_player = player;
}


ItemMgr::~ItemMgr()
{
	for (auto item : _itemList) {
		delete item;
	}
}

bool ItemMgr::update()
{
	for (list<Item*>::iterator it = _itemList.begin(); it != _itemList.end();) {
		if ((*it)->update() == false) {
			it = _itemList.erase(it);
			continue;
		}
		else {
			float x = _player->getX() - (*it)->getX();
			float y = _player->getY() - (*it)->getY();
			float r = (*it)->getRange();
			if (x*x + y*y < r*r) {
				switch ((*it)->getItemType()) {
					case eItemType_PowerSmall:
						GameData::getIns()->power += 1;
						if (GameData::getIns()->power > 500) {
							GameData::getIns()->power = 500;
						}
						GameData::getIns()->plusScore(1.0, GameData::eScorePowerItem);
						break;
					case eItemType_PowerLarge:
						GameData::getIns()->power += 10;
						if (GameData::getIns()->power > 500) {
							GameData::getIns()->power = 500;
						}
						GameData::getIns()->plusScore(10.0, GameData::eScorePowerItem);
						break;
					case eItemType_ScoreSmall:
					{
						double rate = 1;
						if ((*it)->isAuto() == false)	//上部回収以外は、座標で得点が減少
							rate = 1-(_player->getY() - GameData::getIns()->getItemGetBorderLineH()) / (OUT_H - GameData::getIns()->getItemGetBorderLineH());
						GameData::getIns()->plusScore(rate, GameData::eScorePointItem);
						GameData::getIns()->point += 1;
						break;
					}
					case eItemType_ScoreLarge:
					{
						double rate = 10;
						if ((*it)->isAuto() == false)	//上部回収以外は、座標で得点が減少
							rate = 1-(_player->getY() - GameData::getIns()->getItemGetBorderLineH()) / (OUT_H - GameData::getIns()->getItemGetBorderLineH());
						GameData::getIns()->plusScore(rate, GameData::eScorePointItem);
						GameData::getIns()->point += 10;
						break;
					}
					case eItemType_MoneySmall:
						if (!Replayer::getIns()->isReplaying()) {
							GameData::getIns()->setMoney(GameData::getIns()->getMoney() + 1);
						}
						GameData::getIns()->plusScore(1.0, GameData::eScorePowerItem);
						break;
					case eItemType_MoneyLarge:
						if (!Replayer::getIns()->isReplaying()) {
							GameData::getIns()->setMoney(GameData::getIns()->getMoney() + 10);
						}
						GameData::getIns()->plusScore(10.0, GameData::eScorePowerItem);
						break;
					case eItemType_Bomb:
						GameData::getIns()->bomb += BOMB_PARTS_N;
						GameData::getIns()->plusScore(5.0, GameData::eScorePowerItem);
						break;
					case eItemType_BombParts:
						GameData::getIns()->bomb += 1;
						GameData::getIns()->plusScore(1.0, GameData::eScorePowerItem);
						break;
					case eItemType_Empty:
						GameData::getIns()->plusScore(1.0, GameData::eScorePowerItem);
						break;
				}
				SE::getIns()->setPlay(eSE::eSE_getItem);
				it = _itemList.erase(it);
				continue;
			}
			r = GameData::getIns()->absorbRange;
			if (SavedData::getIns()->dat.isEquiped[eEquipItem_Ring]) {
				r *= 1.3;
			}
			if (SavedData::getIns()->dat.isEquiped[eEquipItem_Ring2]) {
				r *= 1.3;
			}
			if (_player->getY() < GameData::getIns()->getItemGetBorderLineH()) {
				(*it)->setAuto();
			}
			if (_player->isBombing()) {
				(*it)->setAuto();
			}
			if ((*it)->isAuto()) {
				(*it)->setAngle(atan2(_player->getY() - (*it)->getY(), _player->getX() - (*it)->getX()));
			}
			else {
				if (Pad::getIns()->get(ePad::slow) && x*x + y*y < r*r) {
					(*it)->setAngle(atan2(_player->getY() - (*it)->getY(), _player->getX() - (*it)->getX()));
					(*it)->setIsAbsorb(true);
				}
				else {
					(*it)->setIsAbsorb(false);
				}
			}
			it++;
		}
	}
	return true;
}

void ItemMgr::draw()
{
	for (auto &&item : _itemList) {
		item->draw();
	}
}

void ItemMgr::regist(float x, float y, eItemPopType popType)
{
	Item* item;
	eItemType type;
	switch (popType) {
	case eItemPopType_PowerSmall:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_PowerSmall);
		_itemList.push_back(item);
		break;
	case eItemPopType_PowerLarge:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_PowerLarge);
		_itemList.push_back(item);
		break;
	case eItemPopType_PowerMany:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_PowerLarge);
		_itemList.push_back(item);
		for (int i = 0; i < 5; i++) {
			item = new Item(x + randf2(70), y + randf2(70), eItemType_PowerSmall);
			_itemList.push_back(item);
		}
		break;
	case eItemPopType_ScoreSmall:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_ScoreSmall);
		_itemList.push_back(item);
		break;
	case eItemPopType_ScoreLaege:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_ScoreLarge);
		_itemList.push_back(item);
		break;
	case eItemPopType_ScoreMany:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_ScoreLarge);
		_itemList.push_back(item);
		for (int i = 0; i < 5; i++) {
			item = new Item(x + randf2(70), y + randf2(70), eItemType_ScoreSmall);
			_itemList.push_back(item);
		}
		break;
	case eItemPopType_MoneySmall:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_MoneySmall);
		_itemList.push_back(item);
		break;
	case eItemPopType_MoneyLarge:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_MoneyLarge);
		_itemList.push_back(item);
		break;
	case eItemPopType_MoneyMany:
		item = new Item(x + randf2(5), y + randf2(5), eItemType_MoneyLarge);
		_itemList.push_back(item);
		for (int i = 0; i < 5; i++) {
			item = new Item(x + randf2(70), y + randf2(70), eItemType_MoneySmall);
			_itemList.push_back(item);
		}
		break;
	case eItemPopType_Bomb:
		item = new Item(x, y, eItemType_Bomb);
		_itemList.push_back(item);
		break;
	case eItemPopType_BombParts:
		item = new Item(x, y, eItemType_BombParts);
		_itemList.push_back(item);
		break;
	}
}
