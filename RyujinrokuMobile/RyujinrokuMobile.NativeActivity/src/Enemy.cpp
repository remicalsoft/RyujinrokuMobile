#include "Enemy.h"
#include "EnemyMover.h"
#include "Image.h"
#include <DxLib.h>
#include "GameData.h"
#include "Utils.h"
#include "SavedData.h"

using namespace std;

Enemy::Enemy(Script script, BarrageRegistable* b)
{
	_isNotAppearedYet = true;
	_isAlive	= true;
	_script		= script;
	_x = script.x + script.xrand;
	_y = script.y + script.yrand;
	_hp = script.hp;
	_maxHp = _hp;
	_counter = 0;
	_imgSizeW = 54;
	_imgSizeH = 54;
	_range = 50;
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone]) {
		_range += 19;
	}
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone2]) {
		_range += 19;
	}
	_v = 0;
	_angle = 0;
	_barrageRegistable = b;
}

Enemy::~Enemy(){}

bool Enemy::update(){
	EnemyMover::getIns()->update(_this, _script.moveType);
	if (_counter == _script.startTime && _isAlive) {
		_barrageRegistable->regist(GameData::getIns()->level, _this, _script);
	}
	_counter++;
	return _isAlive;
}

void Enemy::draw(){
	if (_isAlive) {
		int img[4] = {0,1,2,1};
		int sub = 3;
		if (cos(_angle)>0.1) {//右向き
			sub = 6;
		}
		if (cos(_angle)<-0.1) {//左向き
			sub = 0;
		}
		int handle = -1;
		switch (_script.enemyType) {
		case 0:
			handle = Image::getIns()->enemyNormal[sub + img[(_counter / 8) % 4]];
			DrawRotaGraph(_x, _y, 1.0, 0.0, handle, TRUE);
			drawHp();
			break;
		case 1:
			handle = Image::getIns()->enemyBig[sub + img[(_counter / 8) % 4]];
			DrawRotaGraph(_x, _y, 1.0, 0.0, handle, TRUE);
			drawHp();
			break;
		case 2:
			DrawRotaGraph(_x, _y, 1.0, PI * 2 / 120 * _counter, Image::getIns()->enemyRotate[0], TRUE);
			DrawRotaGraph(_x, _y, 1.0, PI * 2 / 120 * (_counter+60), Image::getIns()->enemyRotate[1], TRUE);
			break;
		}
	}
}

void Enemy::drawHp() {
	if (_isAlive) {
		int n = 0;
		switch (_script.enemyType) {
		case 0:
			DrawGraphF(_x + 10, _y - 20, Image::getIns()->enemyHpBackShort, TRUE);
			n = _hp * 15 / _maxHp;
			for (int i = 0; i < n; i++) {
				DrawGraphF(_x + 10 + 1 + i, _y - 20, Image::getIns()->enemyHp, TRUE);
			}
			break;
		case 1:
			DrawGraphF(_x + 10, _y - 20, Image::getIns()->enemyHpBack, TRUE);
			n = _hp * 40 / _maxHp;
			for (int i = 0; i < n; i++) {
				DrawGraphF(_x + 10 + 1 + i, _y - 20, Image::getIns()->enemyHp, TRUE);
			}
			break;
		}
	}
}