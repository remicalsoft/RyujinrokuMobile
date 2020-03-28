#include "enemyMgr.h"
#include <DxLib.h>
#include "ScriptReader.h"
#include "GameCounter.h"
#include "Utils.h"
#include "SE.h"
#include "Calculator.h"
#include "GameData.h"
#include "BulletEffectMgr.h"
#include "SavedData.h"
#include "StoreBuyScene.h"

using namespace std;

void EnemyMgr::calcIsHit()
{
	//通常ショットとの当たり判定
	list<shared_ptr<PlayerShot>>* shotList = _player->getShotList();
	for (list<shared_ptr<PlayerShot>>::iterator it = shotList->begin(); it != shotList->end();) {
		float x     = (*it)->getX();
		float y     = (*it)->getY();
		float v     = (*it)->getV();
		float angle = (*it)->getAngle();
		float range = (*it)->getRange();
		bool isHit = false;
		for (list<shared_ptr<Enemy>>::iterator eit = _enemyList.begin(); eit != _enemyList.end();) {
			if ((*eit)->isAppeared()) {
				float ex = (*eit)->getX();
				float ey = (*eit)->getY();
				float eRange = (*eit)->getRange();
				if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone]) {
					eRange *= 1.2;
				}
				if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone2]) {
					eRange *= 1.2;
				}
				if (Utils::isHit(x, y, v, angle, range, ex, ey, eRange)) {
					(*eit)->_hp -= (*it)->getPower();
					int hpper = (*eit)->_hp * 100 / (*eit)->_maxHp;
					int hpmax = (*eit)->_maxHp;
					// The enemy is dead
					if ((*eit)->_hp <= 0) {
						_disappearEffectMgr.regist(ex, ey);
						SE::getIns()->setPlay(eSE_disappear);
						_implItemRegistable->regist(ex, ey, (eItemPopType)(*eit)->_script.itemType);
						(*eit)->_isAlive = false;
						_enemyList.erase(eit);
						GameData::getIns()->plusScore(1.0, GameData::eScoreDestroyEnemy);
					}
					it = shotList->erase(it);
					isHit = true;
					_implBulletEffectRegistable->registBulletEffect(ex, ey);
					if (hpper >= 15 || hpmax < 500) {
						SE::getIns()->setPlay(eSE_hit);
					}
					else {
						SE::getIns()->setPlay(eSE_hitFinal);
					}
					GameData::getIns()->plusScore(1.0, GameData::eScoreAttackEnemy);
					break;
				}
			}
			eit++;
		}
		if (!isHit) {
			it++;
		}
	}

	//ボムとの当たり判定
	for (list<shared_ptr<Enemy>>::iterator eit = _enemyList.begin(); eit != _enemyList.end();) {
		if ((*eit)->isAppeared()) {
			float ex = (*eit)->getX();
			float ey = (*eit)->getY();
			float eRange = (*eit)->getRange();
			if (_player->isBombing()) {
				float px = _player->getX();
				float py = _player->getY();
				float pr = _player->getBombR();
				if (px - pr <= ex && ex <= px + pr && ey <= py) {
					(*eit)->_hp -= _player->getBombPower();
					GameData::getIns()->plusScore(1.0, GameData::eScoreAttackEnemy);
					// The enemy is dead
					if ((*eit)->_hp <= 0) {
						GameData::getIns()->plusScore(1.0, GameData::eScoreDestroyEnemy);
						_disappearEffectMgr.regist(ex, ey);
						SE::getIns()->setPlay(eSE_disappear);
						_implItemRegistable->regist(ex, ey, (eItemPopType)(*eit)->_script.itemType);
						(*eit)->_isAlive = false;
						eit = _enemyList.erase(eit);
						continue;
					}
				}
			}
		}
		eit++;
	}

	for (list<shared_ptr<Enemy>>::iterator eit = _enemyList.begin(); eit != _enemyList.end();) {//プレイヤーのレーザー
		if (_player->isLaserNowShooting()) {
			float ex = (*eit)->getX();
			float ey = (*eit)->getY();
			float eRange = (*eit)->getRange();
			bool isHit = false;
			bool isShift = Pad::getIns()->get(ePad::slow) > 0 ? true : false;
			float x1 = _player->getX() + (isShift ? PLAYER_LASER_W_SLOW_ITVL : PLAYER_LASER_W_ITVL);
			float y1 = _player->getY();
			if (y1 > ey && ex - eRange < x1 && x1 < ex + eRange) {
				(*eit)->_hp -= _player->getLaserDamageValue();
				_implBulletEffectRegistable->registBulletEffect(x1, ey);
				isHit = true;
			}
			float x2 = _player->getX() - (isShift ? PLAYER_LASER_W_SLOW_ITVL : PLAYER_LASER_W_ITVL);
			float y2 = _player->getY();
			if (y2 > ey && ex - eRange < x2 && x2 < ex + eRange) {
				(*eit)->_hp -= _player->getLaserDamageValue();
				_implBulletEffectRegistable->registBulletEffect(x2, ey);
				isHit = true;
			}
			if ((*eit)->_hp <= 0) {
				GameData::getIns()->plusScore(1.0, GameData::eScoreDestroyEnemy);
				_disappearEffectMgr.regist(ex, ey);
				SE::getIns()->setPlay(eSE_disappear);
				_implItemRegistable->regist(ex, ey, (eItemPopType)(*eit)->_script.itemType);
				(*eit)->_isAlive = false;
				eit = _enemyList.erase(eit);
				continue;
			}
			if (isHit) {
				int hpper = (*eit)->_hp * 100 / (*eit)->_maxHp;
				if (hpper >= 15) {
					SE::getIns()->setPlay(eSE_hit);
				}
				else {
					SE::getIns()->setPlay(eSE_hitFinal);
				}
			}
		}
		eit++;
	}

	//敵との当たり判定
	for (auto e : _enemyList) {
		if (e->_isAlive && _player->isInvincible()==false) {
			float w = e->getX()-_player->getX();
			float h = e->getY()-_player->getY();
			float r = 10 + _player->getHitRange();
			if (w*w + h*h < r*r) {
				_player->die();
			}
		}
	}

}

EnemyMgr::EnemyMgr(BarrageRegistable* r, Player* p, ItemRegistable* impl, BulletEffectRegistable* implB)
{
	_barrageResistable = r;
	_player = p;
	Calculator::getIns()->setEnemyListInstance(&_enemyList);
	_implItemRegistable = impl;
	_implBulletEffectRegistable = implB;
}

EnemyMgr::~EnemyMgr()
{
	if (_scriptList != nullptr) {
		delete _scriptList;
		_scriptList = nullptr;
	}
	_enemyList.clear();
}

bool EnemyMgr::initialize()
{
	ScriptReader reader;
	_scriptList = reader.read(GameData::getIns()->level, GameData::getIns()->stage);
	if (_scriptList == nullptr) {
		return false;
	}
	return true;
}

void EnemyMgr::finalize()
{
	if (_scriptList != nullptr) {
		delete _scriptList;
		_scriptList = nullptr;
	}
}

bool EnemyMgr::update()
{
	this->calcIsHit();
	int size;
	int cnt = GameCounter::getIns()->get();
	size = _scriptList->size();
	for (int i = 0; i < size; i++) {
		if (cnt == _scriptList->at(i).count-64) {
			_enemyAppearMgr.regist(_scriptList->at(i).x + _scriptList->at(i).xrand, _scriptList->at(i).y+ _scriptList->at(i).yrand);
		}
		if (cnt == _scriptList->at(i).count) {
				shared_ptr<Enemy> enemy = make_shared<Enemy>(_scriptList->at(i), _barrageResistable);
			enemy->setThis(enemy);
			_enemyList.push_back(enemy);
		}
	}
	for (list<shared_ptr<Enemy>>::iterator it = _enemyList.begin(); it != _enemyList.end();) {
		if ((*it)->update() == false) {
			it = _enemyList.erase(it);
		}
		else {
			it++;
		}
	}
	_disappearEffectMgr.update();
	_enemyAppearMgr.update();
	return true;
}

void EnemyMgr::draw(){
	_enemyAppearMgr.draw();
	for (auto e : _enemyList) {
		e->draw();
	}
	_disappearEffectMgr.draw();
}

void EnemyMgr::drawHp()
{
	for (auto e : _enemyList) {
		e->drawHp();
	}
}

void EnemyMgr::kill()
{
	for (auto e : _enemyList) {
		_disappearEffectMgr.regist(e->getX(), e->getY());
		e->_isAlive = false;
	}
	_enemyList.clear();
}

