#include "Define.h"
#include <math.h>
#include "BarrageEasy.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "ImageBullet.h"
#include "Utils.h"

using namespace std;

void BarrageEasy::Barrage015()
{
	if (_counter % 200 == 30) {
		_boss->moveBit(50);
	}
	if (_counter % 200 == 0) {
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 30; i++) {
				bullet_t dat;
				dat.ang = PI2 / 30 * i;
				dat.x = _boss->getX() + cos(dat.ang) * 100;
				dat.y = _boss->getY() + sin(dat.ang) * 100;
				dat.baseX = _boss->getX();
				dat.baseY = _boss->getY();
				dat.v = 0;
				dat.id = j;
				dat.keepAlive = true;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	if (120 <= _counter % 200 && _counter % 200 < 200) {
		if (_counter % 15 == 0) {
			for (int i = 0; i < 10; i++) {
				bullet_t dat;
				dat.ang = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY()) + PI2 / 10 * i;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.v = 7;
				dat.id = 10;
				dat.type = eBulletType::eOdama;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (0 <= b->dat.id && b->dat.id<10) {
			if (b->dat.counter == 60) {
				b->dat.ang = Calculator::getIns()->getAngleToPlayer(b->dat.baseX, b->dat.baseY) + PI2 / 10 * b->dat.id;
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
			if (60 <= b->dat.counter&& b->dat.counter<90) {
				b->dat.v += 0.2f;
			}
			if (b->dat.counter > 200) {
				b->dat.keepAlive = false;
			}
		}
	}
}

void BarrageEasy::Barrage016()
{
	if (_counter % 9 == 0) {
		bullet_t dat;
		dat.x = _boss->getX() + sin(PI * 2 / 120 * _counter) * 385;
		dat.y = _boss->getY();
		dat.ang = PI / 2;
		dat.v = 0;
		dat.id = 0;
		dat.type = eBulletType::eOfuda;
		dat.color = eBulletColor::eBlue;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
	}
	if (_counter % 150 == 120) {
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		for (int i = 0; i < 15; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI * 2 / 15 * i;
			dat.v = 8;
			dat.id = 1;
			dat.type = eBulletType::eTama;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 100) {
				float px = Calculator::getIns()->getPlayerX();
				float py = Calculator::getIns()->getPlayerY();
				float bsx = _boss->getX();
				float bsy = _boss->getY();
				float blx = b->dat.x;
				float bly = b->dat.y;
				b->dat.ang = atan2((bsy + py) / 2 - bly, (bsx + px) / 2 - blx);
			}
			if (100 <= b->dat.counter && b->dat.counter <= 200) {
				b->dat.v += 0.04;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 30) {
				b->dat.v -= 0.2f;
			}
		}
	}
}

void BarrageEasy::Barrage017()
{
	if (_counter == 0) {
		_boss->setPos(_boss->getX(), 280, 60);
	}
	if (60<_counter % 300 && _counter % 150 == 140) {
		for (int i = 0; i < 12; i++) {
			bullet_t dat;
			dat.ang = PI2 / 12 * i;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.v = 6;
			dat.id = 1;
			dat.type = eBulletType::eOdama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter % 300 == 60) {
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.ang = PI2 / 20 * i;
			dat.x = _boss->getX() - 120 + cos(dat.ang) * 90;
			dat.y = _boss->getY() + 0 + sin(dat.ang) * 90;
			dat.baseX = _boss->getX() - 120;
			dat.baseY = _boss->getY() + 0;
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.ang = PI2 / 20 * i;
			dat.x = _boss->getX() + 120 + cos(dat.ang) * 90;
			dat.y = _boss->getY() + 0 + sin(dat.ang) * 90;
			dat.baseX = _boss->getX() + 120;
			dat.baseY = _boss->getY() + 0;
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (_counter % 300 == 120) {
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.ang = PI2 / 20 * i;
			dat.x = _boss->getX() - 180 + cos(dat.ang) * 90;
			dat.y = _boss->getY() + 0 + sin(dat.ang) * 90;
			dat.baseX = _boss->getX() - 180;
			dat.baseY = _boss->getY() + 0;
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePurple;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.ang = PI2 / 20 * i;
			dat.x = _boss->getX() + 180 + cos(dat.ang) * 90;
			dat.y = _boss->getY() + 0 + sin(dat.ang) * 90;
			dat.baseX = _boss->getX() + 180;
			dat.baseY = _boss->getY() + 0;
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePurple;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (_counter % 300 == 180) {
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.ang = PI2 / 20 * i;
			dat.x = _boss->getX() - 120 + cos(dat.ang) * 90;
			dat.y = _boss->getY() - 120 + sin(dat.ang) * 90;
			dat.baseX = _boss->getX() - 120;
			dat.baseY = _boss->getY() - 120;
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.ang = PI2 / 20 * i;
			dat.x = _boss->getX() + 120 + cos(dat.ang) * 90;
			dat.y = _boss->getY() - 120 + sin(dat.ang) * 90;
			dat.baseX = _boss->getX() + 120;
			dat.baseY = _boss->getY() - 120;
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 60) {
				float y = (Calculator::getIns()->getPlayerY() + b->dat.baseY) / 2 - b->dat.y;
				float x = (Calculator::getIns()->getPlayerX() + b->dat.baseX) / 2 - b->dat.x;
				b->dat.ang = atan2(y, x);
			}
			if (60 <= b->dat.counter&&b->dat.counter < 100) {
				b->dat.v += 0.1f;
			}
		}
	}
}

void BarrageEasy::Barrage018()
{
	if (_counter % 300 == 0) {
		float angle = randf2(PI);
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle - PI2 / 20 * i;
			dat.id = 0;
			dat.v = 5;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 60) {
				b->dat.isAlive = false;
				float angle = randf2(PI);
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI2 / 3 * i;
					dat.id = 1;
					dat.v = 4;
					dat.type = eBulletType::eOfuda;
					dat.color = eBulletColor::ePurple;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (b->dat.id == 1) {
			if (60 <= b->dat.counter&& b->dat.counter < 80) {
				b->dat.v -= 0.2f;
			}
			if (b->dat.counter == 120) {
				b->dat.isAlive = false;
				float angle = randf2(PI);
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI2 / 3 * i + randf2(PI / 6);
					dat.id = 2;
					dat.v = 0.5f;
					dat.type = eBulletType::eOfuda;
					dat.color = eBulletColor::ePink;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (b->dat.id == 2) {
			if (b->dat.counter<15) {
				b->dat.v += 0.1f;
			}
		}
	}
	if (_counter % 300 == 0) {
		float angle = randf2(PI);
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 6; i++) {
				Laser* laser = new Laser();
				laser->color = eLaserColor_Blue;
				laser->angle = angle + PI2 / 6 * i;
				laser->startpt.x = _boss->getX() + cos(laser->angle) * 100;
				laser->startpt.y = _boss->getY() + sin(laser->angle) * 100;
				laser->counter = 0;
				laser->width = 1;
				laser->id = j;
				laser->length = 950;
				laser->hitWidth = 0;

				laser->lphy.conv_flag = 1;
				laser->lphy.conv_base_x = _boss->getX();
				laser->lphy.conv_base_y = _boss->getY();
				laser->lphy.conv_x = laser->startpt.x;
				laser->lphy.conv_y = laser->startpt.y;
				laser->lphy.angle = PI2 / 6 + PI2 / 6 * j;
				laser->lphy.base_ang = laser->angle;
				laser->lphy.time = 120;

				_boss->registLaser(laser);
			}
		}
		SE::getIns()->setPlay(eSE_laser);
	}

	list<Laser*> *laserList = _boss->getLaserList();
	for (auto l : *laserList) {
		int cnt = l->counter;
		int id = l->id;
		if (id == 0 || id == 1) {
			if (cnt == 120) {
				if (id == 0) {
					l->isAlive = false;
				}
			}
			if (120 <= cnt&&cnt <= 140) {
				l->width = (cnt - 120) * 4;
			}
			if (cnt == 140) {
				l->width = 80;
				l->hitWidth = 0.6;
			}
			if (cnt >= 240 && cnt <= 300) {
				if (cnt == 260) {
					l->hitWidth = 0;
				}
				l->width = 80 - 80 * ((cnt - 240) / 60.0);
				if (cnt == 300) {
					l->isAlive = false;
				}
			}
		}
	}
}

/********** 3面ボス **********/

void BarrageEasy::Barrage019()
{
	for (int i = 0; i < 6; i++) {
		if (_counter % 360 == 60 * i + 100) {
			for (int i = 0; i < 8; i++) {
				bullet_t dat;
				dat.ang = PI2 / 8 * i + randf2(PI2 / 10);
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.v = 6;
				dat.id = 1;
				dat.type = eBulletType::eOdama;
				dat.color = eBulletColor::ePurple;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	if (_counter == 0) {
		for (int i = 0; i < 30; i++) {
			bullet_t dat;
			dat.ang = PI2 / 30 * i;
			dat.x = _boss->getX() + cos(dat.ang) * 80;
			dat.y = _boss->getY() + sin(dat.ang) * 80;
			dat.baseX = _boss->getX();
			dat.baseY = _boss->getY();
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			for (int t = 0; t < 5; t++) {
				if (b->dat.counter % 360 == 60 + 30 * t) {
					for (int i = 0; i < 9; i++) {
						bullet_t dat;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.ang = Calculator::getIns()->getAngleToPlayer(dat.baseX, dat.baseY) + PI2 / 9 * i + PI2 / 9 / 5 * t;
						dat.id = 1;
						dat.v = 4;
						dat.type = eBulletType::eOfuda;
						dat.color = eBulletColor::eBlue;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
				}
			}
			for (int t = 0; t < 5; t++) {
				if (b->dat.counter % 360 == 60 + 30 * 5 + 30 * t) {
					for (int i = 0; i < 9; i++) {
						bullet_t dat;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.ang = Calculator::getIns()->getAngleToPlayer(dat.baseX, dat.baseY) - PI2 / 9 * i - PI2 / 9 / 5 * t;
						dat.id = 1;
						dat.v = 4;
						dat.type = eBulletType::eOfuda;
						dat.color = eBulletColor::ePink;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
				}
			}
		}
	}
}

void BarrageEasy::Barrage020()
{
	if (_counter == 0) {
		_boss->setPos(OUT_W / 2, OUT_H / 2, 60);
	}
	if (_counter == 60) {
		for (int i = 0; i < 4; i++) {
			bullet_t dat;
			dat.ang = PI2 / 4 * i;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.v = 0;
			dat.id = i % 2;
			dat.keepAlive = true;
			dat.type = eBulletType::eOdama;
			dat.color = i % 2 ? eBulletColor::eBlue : eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0 || b->dat.id == 1) {
			if (b->dat.counter < 60) {
				if (b->dat.id == 0) {
					b->dat.v += 0.11f;
				}
				else {
					b->dat.v += 0.04f;
				}
			}
			if (b->dat.counter == 100) {
				b->dat.v = 0;
			}
			if (b->dat.counter>160) {
				Utils::rotatePos(&b->dat.x, &b->dat.y, PI2 / 800, _boss->getX(), _boss->getY());
				if (_counter % 30 == 0) {
					for (int i = 0; i < 2; i++) {
						bullet_t dat;
						dat.ang = PI2 / 240 * b->dat.counter + PI2 / 2 * i;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.v = 1.2;
						dat.id = 2;
						dat.type = eBulletType::eOfuda;
						dat.color = b->dat.color;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
					}
				}
			}
		}
	}
}


void BarrageEasy::Barrage021()
{
	if (_counter > 200 && _counter % 360<180 && _counter % 60 == 59) {
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 2 + PI / 2 * i;
			dat.v = 5;
			dat.id = 1;
			dat.type = eBulletType::eOdama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter % 360 == 0) {
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 10; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 10 * i;
				dat.x = _boss->getX() - 300 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() + 50 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() - 300 * (j ? -1 : 1);
				dat.baseY = _boss->getY() + 150;
				dat.v = 0;
				dat.id = 0;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 10; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 10 * i;
				dat.x = _boss->getX() - 150 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() + 0 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() - 150 * (j ? -1 : 1);
				dat.baseY = _boss->getY() + 50;
				dat.v = 0;
				dat.id = 0;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::ePurple;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		float angle = randf2(PI);
		for (int i = 0; i < 10; i++) {
			bullet_t dat;
			dat.ang = angle + PI2 / 10 * i;
			dat.x = _boss->getX() + 0 + cos(dat.ang) * 110;
			dat.y = _boss->getY() - 50 + sin(dat.ang) * 110;
			dat.baseX = _boss->getX() + 0;
			dat.baseY = _boss->getY() - 50;
			dat.v = 0;
			dat.id = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 90) {
				b->dat.ang = atan2((b->dat.y + b->dat.baseY + 160) / 2 - b->dat.y, (b->dat.x + b->dat.baseX) / 2 - b->dat.x);
			}
			if (90 <= b->dat.counter && b->dat.counter < 90 + 40) {
				b->dat.v += 0.1f;
			}
			if (b->dat.counter == 290) {
				b->dat.v = 0.1f;
				SE::getIns()->setPlay(eSE::eSE_freeze);
			}
			if (450 <= b->dat.counter && b->dat.counter < 450 + 40) {
				b->dat.v += 0.1f;
			}
		}
	}
}

void BarrageEasy::Barrage022()
{
	if (_counter % 600 == 0) {

		Laser* laser = new Laser();
		laser->color = eLaserColor_Blue;
		laser->angle = PI / 2;
		laser->startpt.x = 64 + GetRand(385 - 128);
		laser->startpt.y = 0;
		laser->counter = 0;
		laser->width = 1;
		laser->id = 0;
		laser->length = 1000;
		laser->hitWidth = 0;
		_boss->registLaser(laser);
		SE::getIns()->setPlay(eSE_laser);
	}

	if (_counter % 600 == 300) {
		Laser* laser = new Laser();
		laser->color = eLaserColor_Blue;
		laser->angle = PI / 2;
		laser->startpt.x = 448 + 128 + GetRand(385 - 128);
		laser->startpt.y = 0;
		laser->counter = 0;
		laser->width = 1;
		laser->id = 0;
		laser->length = 1000;
		laser->hitWidth = 0;
		_boss->registLaser(laser);
		SE::getIns()->setPlay(eSE_laser);
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (60 <= b->dat.counter && b->dat.counter < 60 + 60) {
				b->dat.v += 0.04f;
			}
		}
	}

	list<Laser*> *laserList = _boss->getLaserList();
	for (auto l : *laserList) {
		int cnt = l->counter;
		int id = l->id;
		if (id == 0) {
			if (60 <= cnt&&cnt <= 80) {
				l->width = (cnt - 60) * 4;
			}
			if (cnt == 80) {
				l->width = 80;
				l->hitWidth = 0.6;
			}
			if (80 <= cnt && cnt <= 180 && cnt % 2) {
				bullet_t dat;
				dat.x = l->startpt.x;
				dat.y = WIN_H / 100.f*(cnt - 80);
				dat.ang = dat.x + PI2 / 30 * (cnt - 140);
				dat.v = 0;
				dat.id = 0;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
			if (cnt >= 220 && cnt <= 280) {
				if (cnt == 230) {
					l->hitWidth = 0;
				}
				l->width = 80 - 80 * ((cnt - 220) / 60.0);
				if (cnt == 280) {
					l->isAlive = false;
				}
			}
		}
	}
}

void BarrageEasy::Barrage023()
{
	if (_counter % 180 == 179) {
		_boss->moveBit(50);
	}
	if (_counter % 460 == 0 || _counter % 460 == 120) {
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 16; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 16 * i - PI;
				dat.x = _boss->getX() - 300 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() + 50 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() - 300 * (j ? -1 : 1);
				dat.baseY = _boss->getY() + 50;
				dat.v = 0;
				dat.id = 0;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 16; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 16 * i - PI;
				dat.x = _boss->getX() - 200 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() + 0 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() - 150 * (j ? -1 : 1);
				dat.baseY = _boss->getY() + 0;
				dat.v = 0;
				dat.id = 1;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::ePurple;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 16; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 16 * i - PI;
				dat.x = _boss->getX() - 100 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() - 50 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() + 0;
				dat.baseY = _boss->getY() - 50;
				dat.v = 0;
				dat.id = 2;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}

	if (_counter % 460 == 230 || _counter % 460 == 230 + 120) {
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 16; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 16 * i - PI;
				dat.x = _boss->getX() - 300 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() + 50 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() - 300 * (j ? -1 : 1);
				dat.baseY = _boss->getY() + 50;
				dat.v = 0;
				dat.id = 3;
				dat.keepAlive = true;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 16; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 16 * i - PI;
				dat.x = _boss->getX() - 200 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() + 0 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() - 150 * (j ? -1 : 1);
				dat.baseY = _boss->getY() + 0;
				dat.v = 0;
				dat.id = 4;
				dat.keepAlive = true;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::ePurple;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		for (int j = 0; j < 2; j++) {
			float angle = randf2(PI);
			for (int i = 0; i < 16; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 16 * i - PI;
				dat.x = _boss->getX() - 100 * (j ? -1 : 1) + cos(dat.ang) * 110;
				dat.y = _boss->getY() - 50 + sin(dat.ang) * 110;
				dat.baseX = _boss->getX() + 0;
				dat.baseY = _boss->getY() - 50;
				dat.v = 0;
				dat.id = 5;
				dat.keepAlive = true;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (60 <= b->dat.counter && b->dat.counter < 60 + 60) {
				b->dat.v -= 0.07f;
			}
		}
		if (b->dat.id == 1) {
			if (90 <= b->dat.counter && b->dat.counter < 90 + 60) {
				b->dat.v -= 0.07f;
			}
		}
		if (b->dat.id == 2) {
			if (120 <= b->dat.counter && b->dat.counter < 120 + 60) {
				b->dat.v -= 0.07f;
			}
		}
		if (b->dat.id == 3) {
			if (60 <= b->dat.counter && b->dat.counter < 60 + 60) {
				b->dat.v += 0.07f;
			}
			if (60 <= b->dat.counter && b->dat.counter < 60 + 120) {
				b->dat.ang += PI / 90;
			}
		}
		if (b->dat.id == 4) {
			if (90 <= b->dat.counter && b->dat.counter < 90 + 60) {
				b->dat.v += 0.07f;
			}
			if (90 <= b->dat.counter && b->dat.counter < 90 + 60) {
				b->dat.ang += PI / 90;
			}
		}
		if (b->dat.id == 5) {
			if (120 <= b->dat.counter && b->dat.counter < 120 + 60) {
				b->dat.v += 0.07f;
			}
			if (120 <= b->dat.counter && b->dat.counter < 120 + 120) {
				b->dat.ang += PI / 90;
			}
		}
		if (b->dat.counter == 300) {
			b->dat.keepAlive = false;
		}
	}
}

void BarrageEasy::Barrage024()
{
	if (_counter % 240 == 0) {
		_boss->setPos(Calculator::getIns()->getPlayerX(), Calculator::getIns()->getPlayerY(), 140);
	}
	if (_counter % 240 == 0) {
		for (int j = 1; j <= 5; j += 4) {
			float angle = randf2(PI);
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / 20 * i;
				dat.x = _boss->getX() + cos(dat.ang) * 35 * j;
				dat.y = _boss->getY() + sin(dat.ang) * 35 * j;
				dat.v = 0;
				dat.id = 0;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	if (_counter % 15 == 0) {
		for (int i = 0; i < 1; i++) {
			bullet_t dat;
			dat.ang = PI2 / 240 * _counter + PI2 / 2 * i;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.v = 0;
			dat.id = 1;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (60 <= b->dat.counter && b->dat.counter < 60 + 60) {
				b->dat.v -= 0.05f;
				b->dat.ang -= PI / 90;
			}
		}
		if (b->dat.id == 1) {
			if (60 <= b->dat.counter && b->dat.counter < 60 + 90) {
				b->dat.v += 0.05f;
			}
		}
	}
}

void BarrageEasy::Barrage025()
{
	const static int N = 16;
	if (_counter % 240 == 239) {
		_boss->moveBit(50);
	}
	if (_counter % 60 == 0) {
		float angle = randf2(PI);
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < N; i++) {
				bullet_t dat;
				dat.ang = angle + PI2 / N * i;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.v = 3.5;
				dat.id = j;
				dat.keepAlive = true;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 120) {
				b->dat.ang += PI / 90;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 120) {
				b->dat.ang -= PI / 90;
			}
		}
		if (b->dat.counter > 300) {
			b->dat.keepAlive = false;
		}
	}
}

void BarrageEasy::Barrage026()
{
	if (_counter == 0) {
		int TIME = 85 * 60;
		_boss->setTime(TIME);
		_boss->setSpellMAXTime(TIME);
	}
	if ((_counter % 240) == 239) {
		_boss->moveBit(50);
	}
	if (_counter % 200 == 199) {
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		for (int i = 0; i < 15; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI2 / 15 * i;
			dat.id = 5;
			dat.v = 2.5;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter <= 34) {
		if (5 <= _counter && _counter <= 34 - 5) {
			float h = (OUT_H - 28);
			bullet_t dat;
			dat.x = 16;
			dat.y = (OUT_H - 14) - h / 34 * _counter;
			dat.ang = 0;
			dat.id = 0;
			dat.v = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (35 <= _counter&&_counter <= 35 + 34) {
		if (35 + 5 <= _counter && _counter <= 35 + 34 - 5) {
			float h = (OUT_H - 28);
			bullet_t dat;
			dat.x = OUT_W - 16;
			dat.y = (OUT_H - 14) - h / 34 * (_counter - 35);
			dat.ang = PI;
			dat.id = 1;
			dat.v = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (35 + 34 <= _counter && _counter < 35 + 34 + 31) {
		if (35 + 34 + 5 <= _counter && _counter <= 35 + 34 + 31 - 5) {
			int cnt = _counter - (35 + 34);
			float w = (OUT_W - 28);
			bullet_t dat;
			dat.x = 14 + w / 31 * cnt;
			dat.y = 16;
			dat.ang = PI / 2;
			dat.id = 2;
			dat.v = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (35 + 34 + 31 <= _counter && _counter < 35 + 34 + 31 + 31) {
		if (35 + 34 + 31 + 5 <= _counter && _counter <= 35 + 34 + 31 + 31 - 5) {
			int cnt = _counter - (35 + 34 + 31);
			float w = (OUT_W - 28);
			bullet_t dat;
			dat.x = OUT_W - 14 - w / 31 * cnt;
			dat.y = OUT_H - 16;
			dat.ang = -PI / 2;
			dat.id = 3;
			dat.v = 0;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0 || b->dat.id == 1 || b->dat.id == 2 || b->dat.id == 3) {
			if (b->dat.counter % (360 + b->dat.id * 29) == 179) {
				bullet_t dat;
				dat.x = b->dat.x;
				dat.y = b->dat.y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
				dat.id = 4;
				dat.v = 1;
				dat.type = eBulletType::eOfuda;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
		if (b->dat.id == 4) {
			if (b->dat.counter < 30) {
				b->dat.v += 0.05;
			}
		}
	}
}
