#include "Define.h"
#include <math.h>
#include "BarrageZakoNormal.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "Utils.h"

using namespace std;

void BarrageZakoNormal::Barrage000() {
	//nothing
}

void BarrageZakoNormal::Barrage001() {
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
			dat.v = 8;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 30) {
			b->dat.v -= 0.2f;
		}
	}
}

void BarrageZakoNormal::Barrage002() {
	if (_enemy->_isAlive) {
		if (_counter % 60 == 0 && _counter<=240) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
			dat.v = 8;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 30) {
			b->dat.v -= 0.2f;
		}
	}
}

void BarrageZakoNormal::Barrage003() {
	if (_enemy->_isAlive) {
		if (_counter % 100 == 0 || _counter % 100 == 10 || _counter % 100 == 20) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = angle - PI / 30 * 1 + PI / 30 * j - PI / 2 + PI / 2 * i;
					dat.v = 8;
					dat.type = _script.bulletType;
					dat.color = _script.bulletColor;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 30) {
			b->dat.v -= 0.2f;
		}
	}
}

void BarrageZakoNormal::Barrage004() {
	if (_enemy->_isAlive) {
		if (_counter % 100 == 0 &&  _counter <= 100*3) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 9; i++) {
				for (int j = i; j < 9; j++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = (_counter/100)%2 ? angle-PI/60*4+PI/60*i : angle+PI/60*4-PI/60*i;
					dat.v = (_counter/100)%2 ? 3+0.2*j: 3+0.2*11-0.2*j;
					dat.type = _script.bulletType;
					dat.color = _script.bulletColor;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
}

void BarrageZakoNormal::Barrage005() {
	if (_enemy->_isAlive) {
		if (_counter%60 == 0 || _counter % 60 == 8 || _counter % 60 == 16) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = PI/2;
			dat.v = 8;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 50) {
			b->dat.v -= 0.1f;
		}
	}
}

void BarrageZakoNormal::Barrage006() 
{
	if (_enemy->_isAlive) {
		if (_counter < 60 && _counter % 2) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = PI2/60*_counter;
			dat.v = 5;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 25) {
			b->dat.v -= 0.2f;
		}
		if (60 < b->dat.counter && b->dat.counter <= 60+60) {
			b->dat.v += 0.1f;
		}
	}
}
void BarrageZakoNormal::Barrage007() 
{
	if (_enemy->_isAlive) {
		if (_counter < 60 && _counter % 2) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 60 * _counter;
				dat.v = 5 + i * 2;
				dat.id = i;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 35) {
			b->dat.v -= 0.2f;
			if (b->dat.v < 0) {
				b->dat.v = 0;
			}
		}
		if (60 < b->dat.counter && b->dat.counter <= 60 + 60) {
			b->dat.v += 0.1f + 0.04*b->dat.id;
		}
	}
}
void BarrageZakoNormal::Barrage008() 
{
	if (_enemy->_isAlive) {
		if (_counter % 12 == 0 && _counter < 180) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x,dat.y)+randf2(PI/4);
			dat.v = 10;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 50) {
			b->dat.v -= 0.1f;
		}
	}
}
void BarrageZakoNormal::Barrage009() 
{
	if (_enemy->_isAlive) {
		if (_counter % 3 == 0 && _counter < 180) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI / 2 - PI2 / 180 * _enemy->_counter +PI2/3*i+randf2(PI/360);
				dat.v = 8;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 50) {
			b->dat.v -= 0.1f;
		}
	}
}
void BarrageZakoNormal::Barrage010() 
{
	if (_enemy->_isAlive) {
		if (_counter % 50 == 0 && _counter < 200) {
			float angle = randf2(PI);
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 20*i + angle;
				dat.v = 8;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 50) {
			b->dat.v -= 0.1f;
		}
	}
}
void BarrageZakoNormal::Barrage011() 
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 2; i++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = angle - PI/30+PI/30*j;
					dat.v = 9 + 3 * i;
					dat.type = _script.bulletType;
					dat.color = _script.bulletColor;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 40) {
			b->dat.v -= 0.1f;
		}
	}
}
void BarrageZakoNormal::Barrage012() 
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = angle;
			dat.v = 12;
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 120) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.counter == 130) {
				b->dat.isAlive = false;
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
				float angle = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				for (int i = 0; i < 11; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI / 4 + PI / 2 / 11 * i;
					dat.v = 1+0.1*i;
					dat.id = 1;
					dat.type = eBulletType::eKome;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
}
void BarrageZakoNormal::Barrage013() 
{
	if (_enemy->_isAlive) {
		if (_counter % 5==0) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = angle + randf2(PI / 30) + PI2/3*i;
				dat.v = 7+randf2(1);
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}
void BarrageZakoNormal::Barrage014() 
{
	if (_enemy->_isAlive) {
		if (_counter % 5 == 0 && _counter<40) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = PI/2;
			dat.v = 3;
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
}
void BarrageZakoNormal::Barrage015() 
{
	if (_enemy->_isAlive) {
		if (_counter % 10 == 0 && _counter<50) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x,dat.y);
			dat.v = 7;
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
		}
	}
}

void BarrageZakoNormal::Barrage016() 
{
	if (_enemy->_isAlive) {
		if (_counter < 40) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y)-PI/2+PI2/40*_counter;
				dat.v = 7+2*i;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 50) {
				b->dat.v -= 0.1f;
			}
		}
	}
}

void BarrageZakoNormal::Barrage017() 
{
	if (_enemy->_isAlive) {
		if (_counter<40 && _counter%2==0) {
			bullet_t dat;
			dat.x = _enemy->_x-200+10*_counter;
			dat.y = _enemy->_y+randf2(40);
			dat.ang = PI/2+randf2(PI/50);
			dat.v = 3+randf2(1);
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
}

void BarrageZakoNormal::Barrage018() 
{
	if (_enemy->_isAlive) {
		if (_counter<120 && _counter % 3 == 0) {
			for (int i = 0; i < 6; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2/120*_counter+PI2/6*i;
				dat.v = 4;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
}

void BarrageZakoNormal::Barrage019() 
{
	if (_enemy->_isAlive) {
		if (_counter==0) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x,dat.y);
				dat.v = 0;
				dat.id = 0;
				dat.val = 0.01 + 0.01*i;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
//			if (b->dat.counter < 50) {
				b->dat.v += b->dat.val;
//			}
		}
	}
}
void BarrageZakoNormal::Barrage020()
{
	if (_enemy->_isAlive) {
		if (_counter < 90 && _counter%20==0) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI2 / 60 + PI2/60*i;
				dat.v = 9;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoNormal::Barrage021()
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI/180+PI/180*i;
				dat.v = 8;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoNormal::Barrage022()
{
	if (_enemy->_isAlive) {
		if (_counter%7 == 0) {
			for (int i = 0; i < 12; i++) {
				bullet_t dat;
				dat.x = _enemy->_x + cos(PI2 / 12 * i) * 40;
				dat.y = _enemy->_y + sin(PI2 / 12 * i) * 40;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
				dat.v = 14+randf2(3);
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoNormal::Barrage023()
{
	if (_enemy->_isAlive) {
		if (_counter % 6 == 0) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y)-PI/10+PI/10*i;
				dat.v = 16;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = i==1?eBulletColor::ePink:eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoNormal::Barrage024()
{
	if (_enemy->_isAlive) {
		if (_counter % 6 == 0 && _counter<240) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x+randf2(100);
				dat.y = _enemy->_y+randf2(20);
				dat.ang = Calculator::getIns()->getAngleToPlayer(_enemy->getX(), _enemy->getY());
				dat.v = 0;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 240) {
				b->dat.v += 0.06;
			}
		}
	}
}

void BarrageZakoNormal::Barrage025()
{
	if (_enemy->_isAlive) {
		if (_counter % 5 == 0 && _counter<120) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y)+randf2(PI/2);
				dat.v = 10;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoNormal::Barrage026()
{
	if (_enemy->_isAlive) {
		if (_counter % 3 == 0 && _counter<240) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = PI2/4*i+PI2/120*_counter*1.01;
				dat.v = 9;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoNormal::Barrage027()
{
	if (_enemy->_isAlive) {
		if (_counter % 3 == 0 && _counter<240) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = PI2 / 4 * i - PI2 / 120 * _counter*1.01;
				dat.v = 9;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoNormal::Barrage028()
{
	if (_enemy->_isAlive) {
		if (_counter % 3 == 0 && _counter<500) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					bullet_t dat;
					dat.x = _enemy->getX();
					dat.y = _enemy->getY();
					dat.ang = PI2 / 4 * i - PI2*1.13 / 120 * _counter;
					dat.v = 5+2*j;
					dat.id = 0;
					dat.type = eBulletType::eKome;
					dat.color = eBulletColor::eLime;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (_counter % 10 == 0 && _counter<500) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					bullet_t dat;
					dat.x = _enemy->getX();
					dat.y = _enemy->getY();
					dat.ang = PI2 / 4 * i - PI2*1.11 / 97 * _counter;
					dat.v = 5+2*j;
					dat.id = 0;
					dat.type = eBulletType::eKome;
					dat.color = eBulletColor::eOrenge;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
}

void BarrageZakoNormal::Barrage029()
{
	if (_enemy->_isAlive) {
		if (_counter % 3 != 0 && _counter < 440) {
			bullet_t dat;
			dat.x = _enemy->getX()+randf2(400);
			dat.y = _enemy->getY()+randf2(180);
			dat.ang = Calculator::getIns()->getAngleToPlayer(_enemy->getX(), _enemy->getY());
			dat.v = 0;
			dat.id = _counter/2;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (440<_counter&&_counter<640) {
			b->dat.v += 0.04 + b->dat.id / 10000.f;
		}
	}
}

void BarrageZakoNormal::Barrage030()
{
	if (_enemy->_isAlive) {
		if (_counter % 60 == 10 && _counter < 240) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = Calculator::getIns()->getAngleToPlayer(_enemy->getX(), _enemy->getY()) - PI/4 + PI/4*i;
				dat.v = 8;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (_counter<40) {
			b->dat.v -= 0.1;
		}
	}
}

void BarrageZakoNormal::Barrage031()
{
	if (_enemy->_isAlive) {
		if (_counter % 3 == 0 && _counter < 180) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					bullet_t dat;
					dat.x = _enemy->_x-5+5*j;
					dat.y = _enemy->_y;
					dat.ang = PI / 2 - PI2 / 180 * _enemy->_counter + PI2 / 3 * i + randf2(PI / 360);
					dat.v = 8;
					dat.type = _script.bulletType;
					dat.color = _script.bulletColor;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 50) {
			b->dat.v -= 0.1f;
		}
	}
}

void BarrageZakoNormal::Barrage032()
{
	if (_enemy->_isAlive) {
		if (_counter % 50 == 0 && _counter < 200) {
			float angle = randf2(PI);
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.x = _enemy->_x-5;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 20 * i + angle;
				dat.v = 8;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
			angle = randf2(PI);
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.x = _enemy->_x+5;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 20 * i + angle;
				dat.v = 8;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 50) {
			b->dat.v -= 0.1f;
		}
	}
}

void BarrageZakoNormal::Barrage033()
{
}

void BarrageZakoNormal::Barrage034()
{
}

void BarrageZakoNormal::Barrage035()
{
}

void BarrageZakoNormal::Barrage036()
{
}

void BarrageZakoNormal::Barrage037()
{
}

void BarrageZakoNormal::Barrage038()
{
}

void BarrageZakoNormal::Barrage039()
{
}

void BarrageZakoNormal::Barrage040()
{
}

void BarrageZakoNormal::Barrage041()
{
}

void BarrageZakoNormal::Barrage042()
{
}

void BarrageZakoNormal::Barrage043()
{
}

void BarrageZakoNormal::Barrage044()
{
}

void BarrageZakoNormal::Barrage045()
{
}

void BarrageZakoNormal::Barrage046()
{
}

void BarrageZakoNormal::Barrage047()
{
}

void BarrageZakoNormal::Barrage048()
{
}

void BarrageZakoNormal::Barrage049()
{
}

void BarrageZakoNormal::Barrage050()
{
}

void BarrageZakoNormal::Barrage051() {}
void BarrageZakoNormal::Barrage052() {}
void BarrageZakoNormal::Barrage053() {}
void BarrageZakoNormal::Barrage054() {}
void BarrageZakoNormal::Barrage055() {}
void BarrageZakoNormal::Barrage056() {}
void BarrageZakoNormal::Barrage057() {}
void BarrageZakoNormal::Barrage058() {}
void BarrageZakoNormal::Barrage059() {}
void BarrageZakoNormal::Barrage060() {}
void BarrageZakoNormal::Barrage061() {}
void BarrageZakoNormal::Barrage062() {}
void BarrageZakoNormal::Barrage063() {}
void BarrageZakoNormal::Barrage064() {}
void BarrageZakoNormal::Barrage065() {}
void BarrageZakoNormal::Barrage066() {}
void BarrageZakoNormal::Barrage067() {}
void BarrageZakoNormal::Barrage068() {}
void BarrageZakoNormal::Barrage069() {}
void BarrageZakoNormal::Barrage070() {}
void BarrageZakoNormal::Barrage071() {}
void BarrageZakoNormal::Barrage072() {}
void BarrageZakoNormal::Barrage073() {}
void BarrageZakoNormal::Barrage074() {}
void BarrageZakoNormal::Barrage075() {}
void BarrageZakoNormal::Barrage076() {}
void BarrageZakoNormal::Barrage077() {}
void BarrageZakoNormal::Barrage078() {}
void BarrageZakoNormal::Barrage079() {}
void BarrageZakoNormal::Barrage080() {}
void BarrageZakoNormal::Barrage081() {}
void BarrageZakoNormal::Barrage082() {}
void BarrageZakoNormal::Barrage083() {}
void BarrageZakoNormal::Barrage084() {}
void BarrageZakoNormal::Barrage085() {}
void BarrageZakoNormal::Barrage086() {}
void BarrageZakoNormal::Barrage087() {}
void BarrageZakoNormal::Barrage088() {}
void BarrageZakoNormal::Barrage089() {}
void BarrageZakoNormal::Barrage090() {}
void BarrageZakoNormal::Barrage091() {}
void BarrageZakoNormal::Barrage092() {}
void BarrageZakoNormal::Barrage093() {}
void BarrageZakoNormal::Barrage094() {}
void BarrageZakoNormal::Barrage095() {}
void BarrageZakoNormal::Barrage096() {}
void BarrageZakoNormal::Barrage097() {}
void BarrageZakoNormal::Barrage098() {}
void BarrageZakoNormal::Barrage099() {}

BarrageZakoNormal::BarrageZakoNormal(std::shared_ptr<Enemy> enemy, Script script, IPlayerInfoGettable *impl, BulletEffectRegistable* implBulletDisappearEffectRegistable) : BarrageZako(enemy, script, impl, implBulletDisappearEffectRegistable)
{
}

BarrageZakoNormal::~BarrageZakoNormal()
{
}

