#include "Define.h"
#include <math.h>
#include "BarrageEasy.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "ImageBullet.h"
#include "Utils.h"

using namespace std;

void BarrageEasy::Barrage006()
{
	if (_counter % 300 == 0) {
		float angle = randf2(PI);
		for (int i = 0; i < 25; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI * 2 / 25 * i;
			dat.v = 10;
			dat.id = 0;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter % 300 == 120) {
		float angle = randf2(PI);
		for (int i = 0; i < 25; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI * 2 / 25 * i;
			dat.v = 10;
			dat.id = 1;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < IN_X + 20 || IN_X + IN_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
	}
}

void BarrageEasy::Barrage007()
{

	if (_counter % 300 == 0 || _counter % 300 == 10) {
		float angle = randf2(PI / 20);
		for (int i = 0; i < 15; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle - PI / 2 - PI / 15 * i;
			dat.v = 10;
			dat.id = 0;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter % 300 == 120 || _counter % 300 == 130) {
		float angle = randf2(PI / 20);
		for (int i = 0; i < 15; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle - PI / 2 + PI / 15 * i;
			dat.v = 10;
			dat.id = 1;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < IN_X + 20 || IN_X + IN_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
	}
}


void BarrageEasy::Barrage008()
{
	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 200, +500, eLauncherType_Hanabi));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -200, +500, eLauncherType_Hanabi));
	}
	if (_counter < Launcher::TIME) {
		return;
	}
	if (_counter % 1100 == Launcher::TIME + 60) {
		bullet_t dat;
		dat.x = _boss->getX() + 200;
		dat.y = _boss->getY() + 500;
		dat.ang = -PI / 2;
		dat.v = 10;
		dat.id = 0;
		dat.type = eBulletType::eSmall;
		dat.color = eBulletColor::eBlue;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_hanabiShot);
	}
	if (_counter % 1100 == Launcher::TIME + 60 + 550) {
		bullet_t dat;
		dat.x = _boss->getX() - 200;
		dat.y = _boss->getY() + 500;
		dat.ang = -PI / 2;
		dat.v = 10;
		dat.id = 0;
		dat.type = eBulletType::eSmall;
		dat.color = eBulletColor::eBlue;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_hanabiShot);
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 100) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.counter == 100) {
				b->dat.isAlive = false;
				SE::getIns()->setPlay(eSE::eSE_hanabiExplosion);
				for (int j = 0; j < 22; j++) {
					float angle = randf2(PI / 80);
					for (int i = 0; i < 30; i++) {
						bullet_t dat;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.ang = angle + PI2 / 30 * i;
						dat.v = 0.4 + 0.2*j;
						dat.id = 1;
						dat.isAddBlend = true;
						dat.type = eBulletType::eKome;
						dat.color = eBulletColor::eBlue + j % 8;
						_list.push_back(new Bullet(&dat));
					}
				}
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter > 240) {
				b->dat.v += 0.015f;
			}
		}
	}
}

void BarrageEasy::Barrage009()
{
	if (_counter % 600 < 150 && _counter % 3 == 0) {
		int t = _counter % 600;
		bullet_t dat;
		dat.x = _boss->_x;
		dat.y = _boss->_y;
		dat.ang = PI / 2 - PI2 / 100 + PI2 / 100 * t;
		dat.v = 10;
		dat.id = 0;
		dat.type = eBulletType::eBarrier;
		dat.color = eBulletColor::eBlue;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
	}
	if (300 <= _counter % 600 && _counter % 600 < 450 && _counter % 3 == 0) {
		int t = _counter % 600;
		for (int i = 0; i < 2; i++) {
			bullet_t dat;
			dat.x = _boss->_x;
			dat.y = _boss->_y;
			dat.ang = PI / 2 + PI2 / 100 + PI2 / 100 * t;
			dat.v = 10;
			dat.id = 1;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < IN_X + 20 || IN_X + IN_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
	}
}

void BarrageEasy::Barrage010()
{
	const int LANCH_X1 = _boss->getX() - 370;
	const int LANCH_X2 = _boss->getX() + 370;
	const int LANCH_Y1 = WIN_H - 30;
	const int LANCH_Y2 = WIN_H - 30;

	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 370, WIN_H - OUT_H / 6 - 30, eLauncherType_Hanabi));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -370, WIN_H - OUT_H / 6 - 30, eLauncherType_Hanabi));
	}
	if (_counter < Launcher::TIME) {
		return;
	}
	if (_counter % 180 == Launcher::TIME) {
		if ((_counter / 180) % 2) {
			SE::getIns()->setPlay(eSE::eSE_hanabiFukidashi);
		}
		else {
			SE::getIns()->setPlay(eSE::eSE_hanabiFukidashi2);
		}
	}
	if (_counter >= Launcher::TIME) {
		float v = 20;
		int id = 0;
		if (_counter < Launcher::TIME + 60) {
			int t = _counter - (Launcher::TIME);
			v = 8 + t / 60.f * 12;
		}
		float ang = PI / 30;
		if (Launcher::TIME + 60 < _counter && _counter < Launcher::TIME + 60 + 70) {
			int t = _counter - (Launcher::TIME + 60);
			float div = 30 - 24 * t / 70;
			ang = PI / div;
		}
		else if (Launcher::TIME + 60 + 70 <= _counter) {
			ang = PI / 6;
			id = 1;
		}
		for (int i = 0; i < 8; i++) {
			bullet_t dat;
			dat.x = LANCH_X1;
			dat.y = LANCH_Y1;
			dat.ang = -PI / 2 + randf2(ang);
			dat.v = v;
			dat.id = id;
			dat.isAddBlend = true;
			dat.type = eBulletType::eUmaibo;
			dat.color = eBulletColor::eBlue + GetRand(7);
			_list.push_back(new Bullet(&dat));
		}
		for (int i = 0; i < 8; i++) {
			bullet_t dat;
			dat.x = LANCH_X2;
			dat.y = LANCH_Y2;
			dat.ang = -PI / 2 + randf2(ang);
			dat.v = v;
			dat.id = id;
			dat.isAddBlend = true;
			dat.type = eBulletType::eUmaibo;
			dat.color = eBulletColor::eBlue + GetRand(7);
			_list.push_back(new Bullet(&dat));
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 1) {
			if (63 + 50 < b->dat.x && b->dat.x < 833 - 50) {
				if (GetRand(800) == 0) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = PI / 2;
					dat.v = 0;
					dat.id = 2;
					dat.isAddBlend = true;
					dat.type = eBulletType::eSmall;
					dat.color = b->dat.color;
					_list.push_back(new Bullet(&dat));
				}
			}
		}
		if (b->dat.id == 2) {
			b->dat.v += 0.03f;
		}
	}
}

void BarrageEasy::Barrage011()
{
	for (int t = 0; t < 6; t++) {
		if (_counter % 400 == 20 * t) {
			float x = _boss->_x + 150 + randf2(150);
			if ((_counter / 20) % 2) {
				x = _boss->_x - 150 + randf2(150);
			}
			float y = randf2(100);
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.x = x;
				dat.y = _boss->_y + y;
				dat.ang = PI2 / 20 * i;
				dat.v = 10;
				dat.id = 0;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (int t = 0; t < 6; t++) {
		if (_counter % 400 == 200 + 20 * t) {
			float x = _boss->_x + 150 + randf2(150);
			if ((_counter / 20) % 2) {
				x = _boss->_x - 150 + randf2(150);
			}
			float y = randf2(100);
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.x = x;
				dat.y = _boss->_y + y;
				dat.ang = PI2 / 20 * i;
				dat.v = 10;
				dat.id = 0;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter<70) {
				b->dat.v -= 0.08f;
			}
		}
	}
}

void BarrageEasy::Barrage012()
{
	const static int posN = 6;
	const static float posx[posN] = { -55 - 110 * 2, -55 - 110, -55, 55,55 + 110,55 + 110 * 2 };
	const static float posy[posN] = { 500, 500, 500, 500, 500, 500 };

	if (_counter == 0) {
		for (int i = 0; i < posN; i++) {
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), posx[i], posy[i], eLauncherType_Hanabi));
		}
	}
	if (_counter < Launcher::TIME) {
		return;
	}
	if (Launcher::TIME + 60 <= _counter % 1100 && _counter % 1100 <= Launcher::TIME + 60 + 420) {
		if (_counter % 80 == Launcher::TIME) {
			int r = GetRand(2);
			bullet_t dat;
			dat.x = _boss->getX() + posx[r];
			dat.y = _boss->getY() + posy[r];
			dat.ang = -PI / 2;
			dat.v = 10;
			dat.id = 0;
			dat.type = eBulletType::eSmall;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_hanabiShot);
		}
		if (_counter % 80 == Launcher::TIME) {
			int r = GetRand(2) + 3;
			bullet_t dat;
			dat.x = _boss->getX() + posx[r];
			dat.y = _boss->getY() + posy[r];
			dat.ang = -PI / 2;
			dat.v = 10;
			dat.id = 0;
			dat.type = eBulletType::eSmall;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_hanabiShot);
		}
	}
	if (850 <= _counter % 1100 && _counter % 1100 < 950) {
		if (_counter % 10 == 0) {
			int t = (_counter % 1100 - 850) / 10;
			for (int i = 0; i < 12; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - 400 + 80 * t;
				dat.y = _boss->getY() - 50;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) + PI2 / 12 * i;
				dat.v = 5;
				dat.id = 2;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (1000 <= _counter % 1100 && _counter % 1100 < 1100) {
		if (_counter % 10 == 0) {
			int t = (_counter % 1100 - 1000) / 10;
			float ang = randf2(PI / 20);
			for (int i = 0; i < 12; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - 400 + 80 * t;
				dat.y = _boss->getY() - 50;
				dat.ang = ang + PI2 / 12 * i;
				dat.v = 5;
				dat.id = 2;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 100) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.counter == 100) {
				b->dat.isAlive = false;
				SE::getIns()->setPlay(eSE::eSE_hanabiExplosion);
				for (int i = 0; i < 12; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = randf2(PI);
					dat.v = 10 + randf2(4);
					dat.id = 1;
					dat.isAddBlend = true;
					dat.type = eBulletType::eSparkSmall;
					dat.color = eBulletColor::eBlue + i % 8;
					_list.push_back(new Bullet(&dat));
				}
			}
			if (b->dat.counter == 100) {
				b->dat.isAlive = false;
				SE::getIns()->setPlay(eSE::eSE_hanabiExplosion);
				for (int i = 0; i < 12; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = randf2(PI);
					dat.v = 10 + randf2(4);
					dat.id = 1;
					dat.isAddBlend = true;
					dat.type = eBulletType::eSparkBig;
					dat.color = eBulletColor::eBlue + i % 8;
					_list.push_back(new Bullet(&dat));
				}
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 140) {
				b->dat.v -= 0.1f;
				if (b->dat.v<0) {
					b->dat.v = 0;
				}
			}
			if (b->dat.counter == 140) {
				b->dat.val = 0.05f + randf2(0.01);
			}
			if (140<b->dat.counter&&b->dat.counter < 140 + 60) {
				b->dat.v += b->dat.val;
			}
		}
	}
}

void BarrageEasy::Barrage013()
{
	if (0 <= _counter % 300 && _counter % 300 < 100) {
		if (_counter % 10 == 0) {
			int t = (_counter % 300) / 10;
			for (int i = 0; i < 12; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - 400 + 80 * t;
				dat.y = _boss->getY() - 50;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) + PI2 / 12 * i;
				dat.v = 6;
				dat.id = 2;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
			}
			for (int i = 0; i < 12; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - 400 + 800 - 80 * t;
				dat.y = _boss->getY() - 50;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) + PI2 / 12 * i;
				dat.v = 6;
				dat.id = 2;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (150 <= _counter % 300 && _counter % 300 < 250) {
		if (_counter % 10 == 0) {
			int t = (_counter % 300 - 150) / 10;
			float ang = randf2(PI / 20);
			for (int i = 0; i < 6; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - 400 + 80 * t;
				dat.y = _boss->getY() - 50;
				dat.ang = ang + PI2 / 6 * i;
				dat.v = 5;
				dat.id = 2;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
			}
			for (int i = 0; i < 6; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - 400 + 800 - 80 * t;
				dat.y = _boss->getY() - 50;
				dat.ang = ang + PI2 / 6 * i;
				dat.v = 5;
				dat.id = 2;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
}

void BarrageEasy::Barrage014()
{
	if (_counter == 0) {
		for (int i = 0; i < 87; i++) {
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -428 + 10 * i, -120, _launcherImage[0]));
		}
	}
	if (_counter % 180 == Launcher::TIME + 60) {
		if ((_counter / 180) % 2) {
			SE::getIns()->setPlay(eSE::eSE_hanabiFukidashi);
		}
		else {
			SE::getIns()->setPlay(eSE::eSE_hanabiFukidashi2);
		}
	}
	if (_counter>Launcher::TIME + 60) {
		for (int i = 0; i < 5; i++) {
			bullet_t dat;
			dat.x = 448 + randf2(420);
			dat.y = 40;
			dat.ang = PI / 2;
			dat.v = 0;
			dat.id = 0;
			dat.isAddBlend = true;
			dat.type = eBulletType::eUmaibo;
			dat.color = eBulletColor::eBlue + GetRand(7);
			_list.push_back(new Bullet(&dat));
		}
	}

	if (_boss->getResidualHp() < 50) {
		if (_remCounter == 0) {
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 0, +500, eLauncherType_Hanabi));
		}
		if (_remCounter % 500 == Launcher::TIME + 60) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY() + 500;
			dat.ang = -PI / 2;
			dat.v = 10;
			dat.id = 2;
			dat.type = eBulletType::eSmall;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_hanabiShot);
		}
		_remCounter++;
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 100) {
				b->dat.v += 0.025f;
			}
			if (b->dat.counter == 140) {
				if (GetRand(5) == 0) {
					b->dat.type = eBulletType::eSparkSmall;
					b->dat.ang = PI / 2 + randf2(PI / 40);
				}
				else {
					b->dat.id = 4;
					b->dat.hit = false;
				}
			}
			if (b->dat.counter == 200) {
				if (GetRand(5) == 0) {
					b->dat.isAlive = false;
					for (int i = 0; i < 1; i++) {
						bullet_t dat;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.ang = PI / 2 + randf2(PI / 30);
						dat.v = b->dat.v + randf2(0.3);
						dat.id = 1;
						dat.type = eBulletType::eSmall;
						dat.color = b->dat.color;
						_list.push_back(new Bullet(&dat));
					}
				}
				else {
					b->dat.id = 4;
					b->dat.hit = false;
				}
			}
		}
		if (b->dat.id == 2) {
			if (b->dat.counter < 100) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.counter == 100) {
				b->dat.isAlive = false;
				SE::getIns()->setPlay(eSE::eSE_hanabiExplosion);
				for (int j = 0; j < 22; j++) {
					float angle = randf2(PI / 180);
					for (int i = 0; i < 20; i++) {
						bullet_t dat;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.ang = angle + PI2 / 20 * i + PI2 / 40;
						dat.v = 0.4 + 0.2*j;
						dat.id = 3;
						dat.isAddBlend = true;
						dat.type = eBulletType::eKome;
						dat.color = eBulletColor::eBlue + j % 8;
						_list.push_back(new Bullet(&dat));
					}
				}
			}
		}
		if (b->dat.id == 3) {
			if (b->dat.counter > 180) {
				b->dat.v += 0.03f;
			}
		}
		if (b->dat.id == 4) {
			b->dat.a -= 8;
			if (b->dat.a < 0) {
				b->dat.isAlive = false;
			}
		}
	}
}
