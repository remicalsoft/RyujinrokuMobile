#include "Define.h"
#include <math.h>
#include "BarrageEasy.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "ImageBullet.h"
#include "Utils.h"

using namespace std;

void BarrageEasy::Barrage000() {
	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -200, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +200, 0, _launcherImage[0]));
	}
	/* if (_counter < Launcher::TIME) {	// 制限時間経過で弾幕終了？
		return;
	}

	int t = Launcher::TIME;	// 経過時間取得
	
	// 練習用弾幕プログラミング
	if (t % 60 == 0) {
		bullet_t dat;	// 仮・弾幕作成データ保存用
		for (int i = 0; i < 8; i++) {
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = _angle;
			dat.v = 4.0;
			dat.type = eBulletType::eOfuda;
			dat.color = (t/60+i)%8;
			_list.push_back(new Bullet(&dat));	// ここで完成した弾幕データをPUSH！
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}*/

	// ↓元のプログラム
	if (_counter < Launcher::TIME) {
		return;
	}
	int t = Launcher::TIME;
	{
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		if (_counter % 180 == t) {
			bullet_t dat;
			dat.x = _boss->getX() - 200;
			dat.y = _boss->getY();
			dat.ang = angle;
			dat.v = 14;
			dat.type = eBulletType::eTama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (_counter % 180 == t) {
			bullet_t dat;
			dat.x = _boss->getX() + 200;
			dat.y = _boss->getY();
			dat.ang = angle;
			dat.v = 14;
			dat.type = eBulletType::eTama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter % 180 == t + 0 || _counter % 180 == t + 10 || _counter % 180 == t + 20 || _counter % 180 == t + 30) {
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle - PI / 10 * 1 + PI / 10 * i;
			dat.v = 14;
			dat.type = eBulletType::eYosei;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 60) {
			b->dat.v -= 0.2f;
		}
	}
}

void BarrageEasy::Barrage001() {
	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -200, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +200, 0, _launcherImage[0]));
	}
	if (_counter < Launcher::TIME) {
		return;
	}
	{
		if (_counter % 150 == 0) {
			float angle = randf2(PI);
			for (int i = 0; i < 6; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - 200;
				dat.y = _boss->getY();
				dat.ang = angle + PI * 2 / 6 * i;
				dat.v = 8;
				dat.id = 0;
				dat.type = eBulletType::eTama;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		if (_counter % 150 == 0) {
			float angle = randf2(PI);
			for (int i = 0; i < 6; i++) {
				bullet_t dat;
				dat.x = _boss->getX() + 200;
				dat.y = _boss->getY();
				dat.ang = angle + PI * 2 / 6 * i;
				dat.v = 8;
				dat.id = 0;
				dat.type = eBulletType::eTama;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	int t = Launcher::TIME;
	for (int i = 0; i < 7; i++) {
		if (_counter % 150 == t + 8 * i) {
			if (i == 0) {
				_angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
			}
			for (int j = 0; j <= i; j++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				if (i % 2) {
					dat.ang = _angle - PI / 80 * (i / 2) + PI / 80 * j;
				}
				else {
					dat.ang = _angle - PI / 80 * (i / 2) + PI / 80 * j + PI/160;
				}
				dat.v = 8;
				dat.id = 1;
				dat.type = eBulletType::eYosei;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 30) {
				b->dat.v -= 0.2f;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 30) {
				b->dat.v -= 0.2f;
			}
		}
	}
}

void BarrageEasy::Barrage002()
{
	if (_counter % 5 == 0 && _counter % 150 < 10) {
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle - PI / 3 * 1 + PI / 3 * i;
			dat.v = 8;
			dat.id = 0;
			dat.type = eBulletType::eTama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.1;
			}
			if (b->dat.counter == 160) {
				b->dat.isAlive = false;
				float angle = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI / 3 * 1 + PI / 3 * i;
					dat.v = 4.5f;
					dat.id = 1;
					dat.type = eBulletType::eTama;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 30) {
				b->dat.v -= 0.1;
			}
		}
	}
}

void BarrageEasy::Barrage003()
{
	if (_counter % 3 == 0 && _counter % 180 < 9) {
		for (int i = 0; i < 2; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = PI / 2 - PI / 7 * 1 + PI / 3.5 * i;
			dat.v = 13;
			dat.id = 0;
			dat.type = eBulletType::eYosei;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter % 4 == 0 && _counter % 120 < 12) {
		for (int i = 0; i < 2; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = PI / 2 - PI / 4 + PI / 2 * i;
			dat.v = 6;
			dat.id = 2 + i;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 130) {
				b->dat.v -= 0.1;
			}
			if (b->dat.counter == 160) {
				b->dat.isAlive = false;
				float angle = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI / 4 * 1 + PI / 4 * i;
					dat.v = 5;
					dat.id = 1;
					dat.type = eBulletType::eYosei;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 30) {
				b->dat.v -= 0.1;
			}
		}
		if (b->dat.id == 2) {
			if (b->dat.counter <= 120) {
				b->dat.v -= 0.05;
			}
			if (b->dat.counter == 120) {
				float px = Calculator::getIns()->getPlayerX();
				float py = Calculator::getIns()->getPlayerY();
				float bx = b->dat.x;
				float by = b->dat.y;
				float angle = atan2(py - by, px - bx);
				b->dat.ang = angle;
				b->dat.id = 4;
				b->dat.counter = 0;

				bullet_t dat;
				dat.x = bx;
				dat.y = by;
				dat.ang = angle - PI / 4;
				dat.v = 0;
				dat.id = 4;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::eGreen;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
		if (b->dat.id == 3) {
			if (b->dat.counter <= 120) {
				b->dat.v -= 0.05;
			}
			if (b->dat.counter == 120) {
				float px = Calculator::getIns()->getPlayerX();
				float py = Calculator::getIns()->getPlayerY();
				float bx = b->dat.x;
				float by = b->dat.y;
				float angle = atan2(py - by, px - bx);
				b->dat.ang = angle;
				b->dat.id = 4;
				b->dat.counter = 0;

				bullet_t dat;
				dat.x = bx;
				dat.y = by;
				dat.ang = angle + PI / 4;
				dat.v = 0;
				dat.id = 4;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::eGreen;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
		if (b->dat.id == 4) {
			if (b->dat.counter < 120) {
				b->dat.v += 0.025;
			}
		}
	}
}

void BarrageEasy::Barrage004()
{
	if (_counter % 3 == 0 && _counter % 200 < 20) {
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle - PI / 4 * 1 + PI / 4 * i;
			dat.v = 6;
			dat.id = 0;
			dat.type = eBulletType::eTama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	if (_counter % 90 == 0 || _counter % 90 == 10 || _counter % 90 == 20) {
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		for (int s = 0; s < 3; s++) {
			for (int i = 0; i < 5; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle - PI / 200 * 2 + PI / 200 * i - PI / 2 + PI / 2 * s;
				dat.v = 1;
				dat.id = 3;
				dat.type = eBulletType::eYosei;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1;
			}
			if (b->dat.counter == 60) {
				b->dat.isAlive = false;
				float angle = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI / 4 * 1 + PI / 4 * i;
					dat.v = 5;
					dat.id = 1;
					dat.type = eBulletType::eTama;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 60) {
				b->dat.v -= 0.1;
			}
			if (b->dat.counter == 60) {
				b->dat.isAlive = false;
				float angle = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = angle - PI / 4 * 1 + PI / 4 * i;
					dat.v = 1;
					dat.id = 2;
					dat.type = eBulletType::eTama;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (b->dat.id == 2) {
			if (b->dat.counter < 120) {
				b->dat.v += 0.05;
			}
		}
		if (b->dat.id == 3) {
			if (b->dat.counter < 100) {
				b->dat.v += 0.05;
			}
		}
	}
}

void BarrageEasy::Barrage005()
{
	const static int DIV = 6;
	if (_counter == 0) {
		_boss->setPos(CENTER_X, OUT_H*0.38, 60);
	}
	if (_counter < 60) {
		return;
	}
	if (_counter == 60) {
		for (int s = 0; s < 6; s++) {
			for (int t = 0; t < DIV; t++) {
				bullet_t dat;
				dat.x = _boss->getX() + cos(PI * 2 / DIV * t) * 230;
				dat.y = _boss->getY() + sin(PI * 2 / DIV * t) * 230;
				dat.ang = PI * 2 / 6 * s;
				dat.v = 0;
				dat.id = s;
				dat.type = eBulletType::eYosei;
				dat.color = eBulletColor::eBlue + s;
				dat.keepAlive = true;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (int t = 0; t < 8; t++) {
		if (_counter % 180 == t * 2) {
			if (t == 0) {
				_angle = Calculator::getIns()->getAngleToPlayer(_boss->_x, _boss->_y);
			}
			for (int i = 0; i < 6; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = _angle + PI * 2 / 6 * i;
				dat.v = 4;
				dat.id = 10;
				dat.type = eBulletType::eYosei;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	float angle = Calculator::getIns()->getAngleToPlayer(_boss->_x, _boss->_y);
	if (_counter % 180 == 50) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI * 2 / 6 * i - PI / 180 / 3 * 3 + PI / 180 / 3 * j;
				dat.v = j <= 3 ? 3 + 0.1*j : 3 + 0.1 * 3 - 0.1*(j - 3);
				dat.id = 11;
				dat.type = eBulletType::eYosei;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	if (_counter % 180 == 60 && _counter>180) {
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->_x, _boss->_y);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI * 2 / 3 * i + PI * 2 / 3 / 4 * j;
				dat.v = 6.5 + j;
				dat.id = 12;
				dat.keepAlive = true;
				dat.type = eBulletType::eYosei;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	if (_boss->getResidualHp() < 60) {
		if (_remCounter % 1000<120 && _remCounter % 5 == 0) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI / 2;
				dat.v = 5;
				dat.id = 20;
				dat.type = eBulletType::eLaser;
				dat.color = eBulletColor::eBlue + ((_remCounter / 5) % eBulletColor::eColorNum);
				_list.push_back(new Bullet(&dat));
			}
			if (_remCounter % 1000 == 0) {
				SE::getIns()->setPlay(eSE::eSE_laser);
			}
		}
		if (_remCounter % 1000>=120 && _remCounter % 1000<200 && _remCounter % 2 == 0) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI / 2 + PI / 1000 * ((_remCounter % 1000) - 120) * (i == 0 ? -1 : 1);
				dat.v = 5;
				dat.id = 20;
				dat.type = eBulletType::eLaser;
				dat.color = eBulletColor::eBlue + ((_remCounter / 5) % eBulletColor::eColorNum);
				_list.push_back(new Bullet(&dat));
			}
			if (_remCounter % 1000 == 120) {
				SE::getIns()->setPlay(eSE::eSE_laser);
			}
		}
		if (_remCounter % 1000<620 && _remCounter % 1000 >= 500 && _remCounter % 5 == 0) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI / 2 + PI / 800 * 300 * (i == 0 ? -1 : 1);
				dat.v = 5;
				dat.id = 20;
				dat.type = eBulletType::eLaser;
				dat.color = eBulletColor::eBlue + ((_remCounter / 5) % eBulletColor::eColorNum);
				_list.push_back(new Bullet(&dat));
			}
			if (_remCounter % 1000 == 500) {
				SE::getIns()->setPlay(eSE::eSE_laser);
			}
		}
		if (_remCounter % 1000>=500 + 120 && _remCounter % 1000<500 + 300 && _remCounter % 2 == 0) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI / 2 + PI / 800 * 300 * (i == 0 ? -1 : 1) - PI / 800 * ((_remCounter % 1000) - 620) * (i == 0 ? -1 : 1);
				dat.v = 5;
				dat.id = 20;
				dat.type = eBulletType::eLaser;
				dat.color = eBulletColor::eBlue + ((_remCounter / 5) % eBulletColor::eColorNum);
				_list.push_back(new Bullet(&dat));
			}
			if (_remCounter % 1000 == 620) {
				SE::getIns()->setPlay(eSE::eSE_laser);
			}
		}
		_remCounter++;
	}
	for (auto b : _list) {
		if (0 <= b->dat.id && b->dat.id < 6) {
			if (b->dat.counter == 90) {
				b->dat.v = 4.2;
			}
			if (90 <= b->dat.counter && b->dat.counter < 90 + 170) {
				b->dat.v -= 4.2 / 170.f;
			}
			if (b->dat.counter == 90 + 170) {
				float posX[6] = {}, posY[6] = {};
				for (auto bl : _list) {
					if (0 <= bl->dat.id && bl->dat.id < 6) {
						posX[bl->dat.id] += bl->dat.x;
						posY[bl->dat.id] += bl->dat.y;
					}
				}
				for (int i = 0; i < 6; i++) {
					_baseX[i] = posX[i] / DIV;
					_baseY[i] = posY[i] / DIV;
				}
			}
			if (b->dat.counter > 90 + 170) {
				float preX = b->dat.x, preY = b->dat.y;
				Utils::rotatePos(&b->dat.x, &b->dat.y, b->dat.id % 2 ? -PI / 540 : PI / 450, _baseX[b->dat.id], _baseY[b->dat.id]);
				b->dat.ang = atan2(b->dat.y - preY, b->dat.x - preX);
			}
		}
		if (b->dat.id == 10) {
			if (b->dat.counter < 120) {
				b->dat.ang += PI * 2 / 120;
			}
		}
		if (b->dat.id == 12) {
			if (b->dat.v > 0) {
				b->dat.v -= 0.1;
				if (b->dat.v < 0) {
					b->dat.v = 0;
				}
			}
			if (b->dat.counter == 120) {
				b->dat.isAlive = false;
				b->dat.keepAlive = false;
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 3; j++) {
						bullet_t dat;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.ang = b->dat.ang + PI - PI / 10 + PI / 10 * 2 * i;
						dat.v = 2.5 + 0.3*j;
						dat.id = 13;
						dat.keepAlive = true;
						dat.type = eBulletType::eYosei;
						dat.color = eBulletColor::eBlue + 1 + j;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
				}
			}
		}
		if (b->dat.id == 13) {
			if (b->dat.counter > 60) {
				b->dat.keepAlive = false;
			}
		}
	}
}
