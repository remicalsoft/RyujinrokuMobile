#include "Define.h"
#include <math.h>
#include "BarrageZakoEasy.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "Utils.h"

using namespace std;

void BarrageZakoEasy::Barrage000() {
	//nothing
}

void BarrageZakoEasy::Barrage001() {
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

void BarrageZakoEasy::Barrage002() {
	if (_enemy->_isAlive) {
		if (_counter % 90 == 0) {
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

void BarrageZakoEasy::Barrage003() {
	if (_enemy->_isAlive) {
		if(_counter<=10){
			if (_counter % 200 == 0 || _counter % 200 == 5 || _counter % 200 == 10) {
				float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						bullet_t dat;
						dat.x = _enemy->_x;
						dat.y = _enemy->_y;
						dat.ang = angle - PI / 50 * 1 + PI / 50 * j - PI / 2 + PI / 2 * i;
						dat.v = 8;
						dat.type = _script.bulletType;
						dat.color = _script.bulletColor;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
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

void BarrageZakoEasy::Barrage004() {
	if (_enemy->_isAlive) {
		if (_counter % 100 == 0 && _counter <= 100 * 3) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 7; i++) {
				for (int j = i; j < 7; j++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = (_counter / 100) % 2 ? angle - PI / 60 * 3 + PI / 60 * i : angle + PI / 60 * 3 - PI / 60 * i;
					dat.v = (_counter / 100) % 2 ? 3 + 0.2*j : 3 + 0.2 * 11 - 0.2*j;
					dat.type = _script.bulletType;
					dat.color = _script.bulletColor;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
}

void BarrageZakoEasy::Barrage005() {
	if (_enemy->_isAlive) {
		if (_counter % 60 == 0 || _counter % 60 == 8 || _counter % 60 == 16) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = PI / 2;
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
void BarrageZakoEasy::Barrage006()
{
	if (_enemy->_isAlive) {
		if (_counter < 60 && _counter % 4 == 0) {
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
		if (60 < b->dat.counter && b->dat.counter <= 60+50) {
			b->dat.v += 0.1f;
		}
	}
}
void BarrageZakoEasy::Barrage007()
{
	if (_enemy->_isAlive) {
		if (_counter < 60) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = PI2 / 60 * _counter;
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
		if (60 < b->dat.counter && b->dat.counter <= 60 + 50) {
			b->dat.v += 0.1f;
		}
	}
}
void BarrageZakoEasy::Barrage008()
{
	if (_enemy->_isAlive) {
		if (_counter % 30 == 0 && _counter < 180) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x,dat.y)+randf2(PI/3);
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

void BarrageZakoEasy::Barrage009()
{
	if (_enemy->_isAlive) {
		if (_counter % 10 == 0 && _counter < 180) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI / 2 - PI2 / 180 * _enemy->_counter + PI2 / 2 * i + randf2(PI / 250);
				dat.v = 7.5;
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
void BarrageZakoEasy::Barrage010()
{
	if (_enemy->_isAlive) {
		if (_counter % 100 == 0 && _counter <= 200) {
			float angle = randf2(PI);
			for (int i = 0; i < 10; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 10 * i + angle;
				dat.v = 7.5;
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
void BarrageZakoEasy::Barrage011()
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 2; i++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = angle - PI / 80 + PI / 80 * j;
					dat.v = 8 + 3 * i;
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
void BarrageZakoEasy::Barrage012()
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
				for (int i = 0; i < 7; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI / 4 + PI / 2 / 7 * i;
					dat.v = 1 + 0.1*i;
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
void BarrageZakoEasy::Barrage013()
{
	if (_enemy->_isAlive) {
		if (_counter % 14 == 0) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = angle + randf2(PI / 60) + PI2 / 3 * i;
				dat.v = 7 + randf2(1);
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}
void BarrageZakoEasy::Barrage014()
{
	if (_enemy->_isAlive) {
		if (_counter % 5 == 0 && _counter<30) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = PI / 2;
			dat.v = 3;
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
}
void BarrageZakoEasy::Barrage015()
{
	if (_enemy->_isAlive) {
		if (_counter % 25 == 0 && _counter<50) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
			dat.v = 7;
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
		}
	}
}

void BarrageZakoEasy::Barrage016()
{
	if (_enemy->_isAlive) {
		if (_counter < 40 && _counter%2==0) {
			for (int i = 0; i < 1; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 2 + PI2 / 40 * _counter;
				dat.v = 7 + 2 * i;
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

void BarrageZakoEasy::Barrage017()
{
	if (_enemy->_isAlive) {
		if (_counter<40 && _counter % 4 == 0) {
			bullet_t dat;
			dat.x = _enemy->_x - 200 + 10 * _counter;
			dat.y = _enemy->_y + randf2(40);
			dat.ang = PI / 2 + randf2(PI / 50);
			dat.v = 3 + randf2(1);
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
}

void BarrageZakoEasy::Barrage018()
{
	if (_enemy->_isAlive) {
		if (_counter<120 && _counter % 6 == 0) {
			for (int i = 0; i < 5; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 120 * _counter + PI2 / 5 * i;
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

void BarrageZakoEasy::Barrage019()
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
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
void BarrageZakoEasy::Barrage020()
{
	if (_enemy->_isAlive) {
		if (_counter < 90 && _counter % 20 == 0) {
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 2; i++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI2 / 200 + PI2 / 100 * i -PI/2/2+PI/2/2*j;
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
}

void BarrageZakoEasy::Barrage021()
{
	if (_enemy->_isAlive) {
		if (_counter == 0 && _counter%2==0) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 180 + PI / 180 * i;
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

void BarrageZakoEasy::Barrage022()
{
	if (_enemy->_isAlive) {
		if (_counter % 20 == 0) {
			for (int i = 0; i < 5; i++) {
				bullet_t dat;
				dat.x = _enemy->_x + cos(PI2 / 5 * i) * 20;
				dat.y = _enemy->_y + sin(PI2 / 5 * i) * 20;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
				dat.v = 6 + randf2(3);
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoEasy::Barrage023()
{
	if (_enemy->_isAlive) {
		if (_counter % 15 == 0) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 4 + PI / 4 * i;
				dat.v = 8;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = i == 1 ? eBulletColor::ePink : eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoEasy::Barrage024()
{
	if (_enemy->_isAlive) {
		if (_counter % 35 == 0 && _counter<240) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _enemy->_x + randf2(100);
				dat.y = _enemy->_y + randf2(20);
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
				b->dat.v += 0.04;
			}
		}
	}
}

void BarrageZakoEasy::Barrage025()
{
	if (_enemy->_isAlive) {
		if (_counter % 15 == 0 && _counter<120) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) + randf2(PI / 2);
				dat.v = 6;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoEasy::Barrage026()
{
	if (_enemy->_isAlive) {
		if (_counter % 6 == 0 && _counter<240) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = PI2 / 4 * i + PI2 / 120 * _counter*1.01;
				dat.v = 5;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoEasy::Barrage027()
{
	if (_enemy->_isAlive) {
		if (_counter % 6 == 0 && _counter<240) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = PI2 / 4 * i - PI2 / 120 * _counter*1.01;
				dat.v = 5;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

void BarrageZakoEasy::Barrage028()
{
	if (_enemy->_isAlive) {
		if (_counter % 14 == 0 && _counter<500) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 2; j++) {
					bullet_t dat;
					dat.x = _enemy->getX();
					dat.y = _enemy->getY();
					dat.ang = PI2 / 4 * i - PI2*1.13 / 120 * _counter;
					dat.v = 3 + 2 * j;
					dat.id = 0;
					dat.type = eBulletType::eKome;
					dat.color = eBulletColor::eLime;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (_counter % 27 == 0 && _counter<500) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					bullet_t dat;
					dat.x = _enemy->getX();
					dat.y = _enemy->getY();
					dat.ang = PI2 / 3 * i - PI2*1.11 / 97 * _counter;
					dat.v = 3.5 + 2 * j;
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

void BarrageZakoEasy::Barrage029()
{
	if (_enemy->_isAlive) {
		if (_counter % 5 == 0 && _counter < 280) {
			bullet_t dat;
			dat.x = _enemy->getX() + randf2(400);
			dat.y = _enemy->getY() + randf2(180);
			dat.ang = Calculator::getIns()->getAngleToPlayer(_enemy->getX(), _enemy->getY());
			dat.v = 0;
			dat.id = _counter / 2;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (280<_counter&&_counter<480) {
			b->dat.v += 0.020 + b->dat.id / 20000.f;
		}
	}
}
void BarrageZakoEasy::Barrage030()
{
	if (_enemy->_isAlive) {
		if (_counter % 60 == 10 && _counter < 240) {
			bullet_t dat;
			dat.x = _enemy->getX();
			dat.y = _enemy->getY();
			dat.ang = Calculator::getIns()->getAngleToPlayer(_enemy->getX(), _enemy->getY());
			dat.v = 8;
			dat.id = 0;
			dat.type = _script.bulletType;
			dat.color = _script.bulletColor;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (_counter<40) {
			b->dat.v -= 0.1;
		}
	}
}

void BarrageZakoEasy::Barrage031()
{
	if (_enemy->_isAlive) {
		if (_counter % 10 == 0 && _counter < 180) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					bullet_t dat;
					dat.x = _enemy->_x - 5 + 10 * j;
					dat.y = _enemy->_y;
					dat.ang = PI / 2 - PI2 / 180 * _enemy->_counter + PI2 / 2 * i + randf2(PI / 250);
					dat.v = 7.5;
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

void BarrageZakoEasy::Barrage032()
{
	if (_enemy->_isAlive) {
		if (_counter % 100 == 0 && _counter <= 200) {
			float angle = randf2(PI);
			for (int i = 0; i < 10; i++) {
				bullet_t dat;
				dat.x = _enemy->_x-5;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 10 * i + angle;
				dat.v = 7.5;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
			angle = randf2(PI);
			for (int i = 0; i < 10; i++) {
				bullet_t dat;
				dat.x = _enemy->_x+5;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 10 * i + angle;
				dat.v = 7.5;
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

void BarrageZakoEasy::Barrage033()
{
}

void BarrageZakoEasy::Barrage034()
{
}

void BarrageZakoEasy::Barrage035()
{
}

void BarrageZakoEasy::Barrage036()
{
}

void BarrageZakoEasy::Barrage037()
{
}

void BarrageZakoEasy::Barrage038()
{
}

void BarrageZakoEasy::Barrage039()
{
}

void BarrageZakoEasy::Barrage040()
{
}

void BarrageZakoEasy::Barrage041()
{
}

void BarrageZakoEasy::Barrage042()
{
}

void BarrageZakoEasy::Barrage043()
{
}

void BarrageZakoEasy::Barrage044()
{
}

void BarrageZakoEasy::Barrage045()
{
}

void BarrageZakoEasy::Barrage046()
{
}

void BarrageZakoEasy::Barrage047()
{
}

void BarrageZakoEasy::Barrage048()
{
}

void BarrageZakoEasy::Barrage049()
{
}

void BarrageZakoEasy::Barrage050()
{
}
void BarrageZakoEasy::Barrage051() {}
void BarrageZakoEasy::Barrage052() {}
void BarrageZakoEasy::Barrage053() {}
void BarrageZakoEasy::Barrage054() {}
void BarrageZakoEasy::Barrage055() {}
void BarrageZakoEasy::Barrage056() {}
void BarrageZakoEasy::Barrage057() {}
void BarrageZakoEasy::Barrage058() {}
void BarrageZakoEasy::Barrage059() {}
void BarrageZakoEasy::Barrage060() {}
void BarrageZakoEasy::Barrage061() {}
void BarrageZakoEasy::Barrage062() {}
void BarrageZakoEasy::Barrage063() {}
void BarrageZakoEasy::Barrage064() {}
void BarrageZakoEasy::Barrage065() {}
void BarrageZakoEasy::Barrage066() {}
void BarrageZakoEasy::Barrage067() {}
void BarrageZakoEasy::Barrage068() {}
void BarrageZakoEasy::Barrage069() {}
void BarrageZakoEasy::Barrage070() {}
void BarrageZakoEasy::Barrage071() {}
void BarrageZakoEasy::Barrage072() {}
void BarrageZakoEasy::Barrage073() {}
void BarrageZakoEasy::Barrage074() {}
void BarrageZakoEasy::Barrage075() {}
void BarrageZakoEasy::Barrage076() {}
void BarrageZakoEasy::Barrage077() {}
void BarrageZakoEasy::Barrage078() {}
void BarrageZakoEasy::Barrage079() {}
void BarrageZakoEasy::Barrage080() {}
void BarrageZakoEasy::Barrage081() {}
void BarrageZakoEasy::Barrage082() {}
void BarrageZakoEasy::Barrage083() {}
void BarrageZakoEasy::Barrage084() {}
void BarrageZakoEasy::Barrage085() {}
void BarrageZakoEasy::Barrage086() {}
void BarrageZakoEasy::Barrage087() {}
void BarrageZakoEasy::Barrage088() {}
void BarrageZakoEasy::Barrage089() {}
void BarrageZakoEasy::Barrage090() {}
void BarrageZakoEasy::Barrage091() {}
void BarrageZakoEasy::Barrage092() {}
void BarrageZakoEasy::Barrage093() {}
void BarrageZakoEasy::Barrage094() {}
void BarrageZakoEasy::Barrage095() {}
void BarrageZakoEasy::Barrage096() {}
void BarrageZakoEasy::Barrage097() {}
void BarrageZakoEasy::Barrage098() {}
void BarrageZakoEasy::Barrage099() {}
BarrageZakoEasy::BarrageZakoEasy(std::shared_ptr<Enemy> enemy, Script script, IPlayerInfoGettable* impl, BulletEffectRegistable* implBulletDisappearEffectRegistable) : BarrageZako(enemy, script, impl, implBulletDisappearEffectRegistable)
{
}

BarrageZakoEasy::~BarrageZakoEasy()
{
}
