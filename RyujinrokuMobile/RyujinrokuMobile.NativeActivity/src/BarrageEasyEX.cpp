#include "Define.h"
#include <math.h>
#include "BarrageEasy.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "ImageBullet.h"
#include "Utils.h"

using namespace std;

// ここからアメヒルネ弾幕です。おかしなソースコードにご注意ください
// Ex 中ボス1通常
void BarrageEasy::Barrage056() {

	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -200, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +200, 0, _launcherImage[0]));
		_angle = 0;
	}

	if (_counter < Launcher::TIME)	return;

	if (_counter % 14 == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI2 / 2 * i + PI / 10 * j + _angle;
				dat.id = 0;
				dat.v = 6;
				dat.type = eBulletType::eYosei;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
			}
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		_angle += PI*1.1 / 8;
	}

	if (_counter % 200 == 0) {		// 敵機外し24way
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 2; j++) {
				bullet_t dat;
				dat.x = _launcher[j]->x;
				dat.y = _launcher[j]->y;
				dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() + PI2 / 12 * i + PI2 / 24;
				dat.v = 6;
				dat.id = 1;
				dat.color = eBulletColor::eYellow;
				dat.type = eBulletType::eYosei;
				_list.push_back(new Bullet(&dat));

			}
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	for (auto b : _list) {
		// 本体弾幕計算
		if (b->dat.id == 1) {
			if (b->dat.v > 3)	b->dat.v -= 0.05;
		}

	}

}

// Ex 中ボス1スペル
// Ex２：７色のワイドスターマイン
void BarrageEasy::Barrage057() {


	if (_counter == 0) {
		_angle = 0;
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +120, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +120, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(2 * PI / 7), 120 * sin(2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(2 * PI / 7), 120 * sin(2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(2 * 2 * PI / 7), 120 * sin(2 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(2 * 2 * PI / 7), 120 * sin(2 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(3 * 2 * PI / 7), 120 * sin(3 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(3 * 2 * PI / 7), 120 * sin(3 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(4 * 2 * PI / 7), 120 * sin(4 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(4 * 2 * PI / 7), 120 * sin(4 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(5 * 2 * PI / 7), 120 * sin(5 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(5 * 2 * PI / 7), 120 * sin(5 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(6 * 2 * PI / 7), 120 * sin(6 * 2 * PI / 7), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 120 * cos(6 * 2 * PI / 7), 120 * sin(6 * 2 * PI / 7), _launcherImage[0]));
	}

	if (_counter < Launcher::TIME) {
		return;
	}

	if (_counter % 150 == 0) {
		_boss->moveBit(50);
	}

	if (_counter % 240 == 0) {
		bullet_t dat;
		for (int i = 0; i < 5; i++) {
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.v = 3.5;
			dat.id = 2;
			dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() + PI2 / 5 * i;
			dat.type = eBulletType::eOdama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
		}
	}

	if (_counter % 10 == 0) {
		for (int i = 0; i < 14; i++) {
			_launcher[i]->x = _boss->getX() + 120 * cos((i / 2) * 2 * PI / 7 + (i % 2 == 0 ? 1 : -1)*_angle);
			_launcher[i]->y = _boss->getY() + 120 * sin((i / 2) * 2 * PI / 7 + (i % 2 == 0 ? 1 : -1)*_angle);
		}

		bullet_t dat;
		for (int i = 0; i < 5; i++) {	// 左回り
			dat.x = _launcher[i * 2]->x;
			dat.y = _launcher[i * 2]->y;
			dat.v = 4.5;
			dat.id = 0;
			dat.ang = i * 2 * PI / 5 + _angle;
			dat.type = eBulletType::eKome;
			dat.isAddBlend = true;
			dat.color = eBulletColor::eLime - i;
			_list.push_back(new Bullet(&dat));
		}
		for (int i = 0; i < 5; i++) {	// 右回り
			dat.x = _launcher[i * 2 + 1]->x;
			dat.y = _launcher[i * 2 + 1]->y;
			dat.v = 5.0;
			dat.id = 1;
			dat.ang = i * 2 * PI / 5 - _angle;
			dat.type = eBulletType::eKome;
			dat.isAddBlend = true;
			dat.color = eBulletColor::eLime - i;
			_list.push_back(new Bullet(&dat));
		}
		_angle += PI * 2 / 40;
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	if (_boss->getResidualHp()<50) {
		for (auto b : _list) {
			if (b->dat.id == 0) {
				if (b->dat.counter > 30)	b->dat.ang -= PI / 1120;
			}
			if (b->dat.id == 1) {
				if (b->dat.counter > 30)	b->dat.ang += PI / 1120;
			}
		}
	}
}

// Ex 中ボス2通常
void BarrageEasy::Barrage058() {
	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -200, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +200, 0, _launcherImage[0]));
		_angle = 0;
	}

	if (_counter < Launcher::TIME)	return;

	if (_counter % 20 == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI2 / 2 * i + PI / 10 * j + _angle;
				dat.id = 0;
				dat.v = 3 + i;
				dat.type = eBulletType::eKome;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI2 / 2 * i - PI / 11 * j - _angle;
				dat.id = 0;
				dat.v = 4 + i;
				dat.type = eBulletType::eKome;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
			}
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		_angle += PI / 18;
	}

	if (_counter % 120 == 0) {		// 敵機外し24way
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 2; j++) {
				bullet_t dat;
				dat.x = _launcher[j]->x;
				dat.y = _launcher[j]->y;
				dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() + PI2 / 12 * i + PI2 / 24;
				dat.v = 4;
				dat.id = 1;
				dat.color = eBulletColor::eYellow;
				dat.type = eBulletType::eYosei;
				_list.push_back(new Bullet(&dat));

			}
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	for (auto b : _list) {
		// 本体弾幕計算
		if (b->dat.id == 1) {
			if (b->dat.v > 3)	b->dat.v -= 0.05;
		}

	}
}

// Ex 中ボス2スペル
// Ex Half-Sp3「死界の領域」
void BarrageEasy::Barrage059() {

	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -300, -_boss->getY(), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +300, -_boss->getY(), _launcherImage[0]));
	}

	if (_counter == Launcher::TIME) {
		for (int i = 0; i < 2; i++) {
			Laser* laser = new Laser();
			laser->color = eLaserColor_Blue;
			laser->angle = PI / 2;
			laser->startpt.x = _launcher[i]->x;
			laser->startpt.y = _launcher[i]->y;
			laser->counter = 0;
			laser->width = 3;
			laser->id = i;
			laser->length = 1300;
			laser->hitWidth = 0;
			_boss->registLaser(laser);
		}
		SE::getIns()->setPlay(eSE_laser);
	}

	if (_counter % 5 == 0) {
		for (int i = 0; i < 5; i++) {
			bullet_t dat;
			dat.x = OUT_W + 10;
			dat.y = GetRand(OUT_H);
			dat.ang = PI;
			dat.id = GetRand(3) + (_counter > Launcher::TIME + 120 ? 0 : 1);
			dat.hit = (_counter > Launcher::TIME + 120 ? true : false);
			dat.v = 4.0 + randf(3.0);
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
	}


	if (_counter >= Launcher::TIME) {
		for (auto b : _list) {
			if (b->dat.id < 10) {
				if (b->dat.x<_launcher[1]->x && b->dat.x>_launcher[0]->x) {
					if (b->dat.id != 0) {
						b->dat.a = 16;
						b->dat.hit = false;
					}
					else {
						_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y, eBulletEffectType_Disappear);
						b->dat.hit = true;
						b->dat.color = eBulletColor::ePink;
						b->dat.v = 0.1;
						b->dat.counter = 0;
						b->dat.id = 10;
					}
				}
				else {
					b->dat.hit = true;
					b->dat.a = 255;
				}
			}
			else if (b->dat.id == 10) {
				if (b->dat.counter < 120) {
					b->dat.v += 0.025;
				}
				if (_launcher[0]->x <= b->dat.x && b->dat.x <= _launcher[1]->x) {
				}
				else if (b->dat.x < CENTER_X) {
					b->dat.color = eBulletColor::eBlue;
				}
			}
		}

		list<Laser*> *laserlist = _boss->getLaserList();
		for (auto l : *laserlist) {
			l->startpt.x = _launcher[l->id]->x;
		}

		if (_counter % 5 == 0) {
			if (_launcher[1]->x - _launcher[0]->x > 200) {
				_launcher[0]->x++;
				_launcher[1]->x--;
			}
		}
	}
}

/* 5 */
// Ex Boss-N1
void BarrageEasy::Barrage060() {

	int t = _counter;
	int tcnt = t % 160;	// １周期分
	float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());

	if (t == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -200, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +200, 0, _launcherImage[0]));
	}

	if (t < Launcher::TIME)	return;
	/*
	// Boss Bullet.(id:0)
	if (t % 10 == 0 && tcnt < 130) {
	for (int i = 0; i < 7; i++) {
	bullet_t dat;
	dat.x = _boss->getX();
	dat.y = _boss->getY();
	dat.ang = angle - 3 * PI / 30 + i*PI / 30;
	dat.v = 6;
	dat.type = eBulletType::eKome;
	dat.color = eBulletColor::eBlue;
	dat.id = 0;
	_list.push_back(new Bullet(&dat));
	SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	}
	*/
	// Launcher Bullet.(id:1)
	if (t % 48 == 0) {
		for (int i = 0; i < 24; i++) {
			bullet_t dat;
			dat.x = _boss->getX() - 200;
			dat.y = _boss->getY();
			dat.ang = angle + i* PI2 / 24;
			dat.v = 2 + i % 2 * 2;
			dat.type = eBulletType::eYosei;
			dat.color = i % eBulletColor::eColorNum;
			dat.id = 1;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		for (int i = 0; i < 24; i++) {
			bullet_t dat;
			dat.x = _boss->getX() + 200;
			dat.y = _boss->getY();
			dat.ang = angle + i * PI2 / 24;
			dat.v = 2 + i % 2 * 2;
			dat.type = eBulletType::eYosei;
			dat.color = i % eBulletColor::eColorNum;
			dat.id = 1;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

}

void BarrageEasy::Barrage061() {

	double rangle;

	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -300, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +300, 0, _launcherImage[0]));
		_angle = 0;
	}

	if (_counter < Launcher::TIME)	return;

	_launcher[0]->x = _boss->getX() + 300 * cos(_angle);
	_launcher[1]->x = _boss->getX() + 300 * cos(_angle + PI);
	_launcher[0]->y = _boss->getY() + 30 * sin(_angle * 3 / 2);
	_launcher[1]->y = _boss->getY() + 30 * sin(_angle * 3 / 2 + PI);

	if (_counter % 50 == 0) {
		rangle = GetRand(360)*PI2 / 360;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 2; j++) {
				bullet_t dat;
				dat.x = _launcher[j]->x;
				dat.y = _launcher[j]->y;
				dat.ang = rangle + i*PI2 / 6;
				dat.v = 4;
				dat.id = 0;
				dat.color = eBulletColor::eOrenge;
				dat.type = eBulletType::eYosei;
				_list.push_back(new Bullet(&dat));
			}
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	/*
	if (_counter % 50 == 0) {
	for (int j = 0; j < 2; j++) {
	bullet_t dat;
	dat.x = _launcher[j]->x;
	dat.y = _launcher[j]->y;
	dat.ang = PI / 2;
	dat.v = 3;
	dat.id = 1;
	dat.color = eBulletColor::ePink;
	dat.type = eBulletType::eLaser;
	_list.push_back(new Bullet(&dat));
	}
	SE::getIns()->setPlay(eSE_laser);
	}
	*/

	if (_counter % 130 == 0) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				bullet_t dat;
				dat.x = _launcher[j]->x;
				dat.y = _launcher[j]->y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 4 + i*PI / 8;
				dat.v = 4.5;
				dat.id = 2;
				dat.color = eBulletColor::eBlue;
				dat.type = eBulletType::eSparkBig;
				_list.push_back(new Bullet(&dat));
			}
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	if (_counter % 140 == 0) {
		float angle = Calculator::getIns()->getAngleFromBossToPlayer();
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle - PI / 80 + PI / 80 * i;
			dat.v = 4.5;
			dat.id = 4;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eOdama;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	if (_counter >= 120 && _counter % 35 == 0) {
		for (int j = 0; j < 2; j++) {
			bullet_t dat;
			dat.x = _launcher[j]->x;
			dat.y = _launcher[j]->y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
			dat.v = 3;
			dat.id = 3;
			dat.color = eBulletColor::eGreen;
			dat.type = eBulletType::eBarrier;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	for (auto b : _list) {
		if (b->dat.id == 3) {
			b->dat.v += 0.01;
		}
	}

	_angle += PI / 180;
}



void BarrageEasy::Barrage062() {

	int t = _counter;	// 経過時間取得
	if (_counter == 0) {
		_angle = Calculator::getIns()->getAngleFromBossToPlayer();
	}

	if (_counter < Launcher::TIME) {
		return;
	}

	// 弾幕プログラミング
	// 本体弾幕（id:0〜5）
	if (_boss->getResidualHp() > 50) {
		if (t % 35 == 0) {
			bullet_t dat;	// 仮・弾幕作成データ保存用
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 4; j++) {
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = _angle + PI2 / 8 * i;
					dat.v = 6.0;
					dat.type = eBulletType::eYosei;
					dat.counter = 0;
					dat.id = j;
					dat.color = (t / 30 + i) % 8;
					_list.push_back(new Bullet(&dat));	// ここで完成した弾幕データをPUSH！
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
			_angle += PI / 36;
		}
	}
	else {
		if (t % 35 == 0) {
			bullet_t dat;	// 仮・弾幕作成データ保存用
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 4; j++) {
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = _angle + PI2 / 8 * i;
					dat.v = 6.0;
					dat.type = eBulletType::eYosei;
					dat.counter = 0;
					dat.id = j;
					dat.color = (t / 30 + i) % 8;
					_list.push_back(new Bullet(&dat));	// ここで完成した弾幕データをPUSH！
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
			_angle += PI / 36;
		}
	}

	for (auto b : _list) {
		// 本体弾幕計算
		if (b->dat.counter < 120)	b->dat.v -= 0.05;
		if (b->dat.counter == 120) {
			b->dat.v = (b->dat.id / 2 + 1.0) * 2;
			if (b->dat.id % 2 == 0)	b->dat.ang += PI / 6;
			else					b->dat.ang -= PI / 6;
		}
		if (b->dat.counter > 120) {
			if (b->dat.id % 2 == 0)		b->dat.ang += PI / 1080;
			else						b->dat.ang -= PI / 1080;
		}
	}
}

void BarrageEasy::Barrage063() {

	if (_counter % 15 == 0) {
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = GetRand(OUT_W);
			dat.y = 0;
			dat.ang = PI / 2;
			dat.v = 4;
			dat.id = 0;
			dat.color = i != 0 ? eBulletColor::eBlue : eBulletColor::ePink;
			dat.type = i != 0 ? eBulletType::eYosei : eBulletType::eKome;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.y > OUT_H * 2 / 3) {
				b->dat.id = 1;
				b->dat.v = 0;
				b->dat.counter = 0;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter > 60) {
				b->dat.id = 2;
				if (b->dat.color == eBulletColor::ePink)
					b->dat.ang = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
			}
		}
		if (b->dat.id == 2) {
			b->dat.v += 0.01;
		}
	}
}

void BarrageEasy::Barrage064() {

	double rangle;

	if (_counter % 300 == 0 && _counter != 0) {
		_boss->moveBit(100);
	}

	if (_counter % 180 == 0) {
		rangle = GetRand(360)*PI2 / 360;
		for (int i = 0; i < 6; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = rangle + PI2 / 6 * i;
			dat.id = 0;
			dat.v = 2.5;
			dat.color = eBulletColor::ePink;
			dat.type = eBulletType::eYosei;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (_counter % 25 == 0) {
		bullet_t dat;

		// ヨコ
		dat.x = 0;
		dat.y = Calculator::getIns()->getPlayerY();
		dat.ang = 0;
		dat.v = 0;
		dat.id = 1;
		dat.color = eBulletColor::ePurple;
		dat.type = eBulletType::eKome;
		_list.push_back(new Bullet(&dat));

		// タテ
		dat.x = Calculator::getIns()->getPlayerX();
		dat.y = 0;
		dat.ang = PI / 2;
		dat.v = 0;
		dat.id = 2;
		dat.color = eBulletColor::eBlue;
		dat.type = eBulletType::eKome;
		_list.push_back(new Bullet(&dat));

		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);

	}

	for (auto b : _list) {
		if (b->dat.id != 0) {
			if (b->dat.v < 4.0) {
				b->dat.v += 0.02;
			}
			if (_counter<600)	continue;
			if (b->dat.x > OUT_W - 20) {
				b->dat.x = OUT_W - 20;
				b->dat.ang += PI;
				b->dat.color = eBulletColor::eLime;
			}
			/*
			if (b->dat.y> OUT_H - 20) {
			b->dat.y = OUT_H - 20;
			b->dat.ang += PI;
			b->dat.color = eBulletColor::eLime;
			}
			*/
		}
	}
}

void BarrageEasy::Barrage065() {

	if (_counter % 60 == 0) {
		float angle = randf2(PI);
		for (int i = 0; i < 22; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI * 2 / 22 * i;
			dat.v = 7;
			dat.id = 0;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 40) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < IN_X + 20 || IN_X + IN_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.color = eBulletColor::ePink;
				b->dat.id = 2;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 40) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.color = eBulletColor::ePink;
				b->dat.id = 2;
			}
		}
	}
}

void BarrageEasy::Barrage066() {

	if (_counter == 0) {
		_angle = 0;
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +100, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +100, 0, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 100 * cos(2 * PI / 3), 50 * sin(2 * PI / 3), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 100 * cos(2 * PI / 3), 50 * sin(2 * PI / 3), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 100 * cos(2 * 2 * PI / 3), 50 * sin(2 * 2 * PI / 3), _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 100 * cos(2 * 2 * PI / 3), 50 * sin(2 * 2 * PI / 3), _launcherImage[0]));
	}

	if (_counter < Launcher::TIME) {
		return;
	}

	if (_counter % 240 == 180) {
		_boss->moveBit(50);
	}

	if (_counter % 5 == 0) {
		for (int i = 0; i < 6; i++) {
			_launcher[i]->x = _boss->getX() + 100 * cos((i / 2) * 2 * PI / 3 + (i % 2 == 0 ? 1 : -1)*_angle);
			_launcher[i]->y = _boss->getY() + 50 * sin((i / 2) * 2 * PI / 3 + (i % 2 == 0 ? 1 : -1)*_angle);
		}

	}
	if (_counter % 13 == 0) {

		bullet_t dat;
		for (int i = 0; i < 3; i++) {	// 左回り
			dat.x = _launcher[i * 2]->x;
			dat.y = _launcher[i * 2]->y;
			dat.v = 4.5;
			dat.id = 0;
			dat.ang = i * 2 * PI / 3 + _angle;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
		}
		for (int i = 0; i < 3; i++) {	// 右回り
			dat.x = _launcher[i * 2 + 1]->x;
			dat.y = _launcher[i * 2 + 1]->y;
			dat.v = 4.5;
			dat.id = 1;
			dat.ang = i * 2 * PI / 3 - _angle;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
		}
		_angle += PI * 2 / 60;
		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
	}


	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 20) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < IN_X + 20 || IN_X + IN_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 20) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
	}

}

void BarrageEasy::Barrage067() {

	if (_counter % 240 == 0) {
		float angle = randf2(PI);
		for (int i = 0; i < 30; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI * 2 / 30 * i;
			dat.v = 6;
			dat.id = 0;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (_counter % 240 == 120) {
		float angle = randf2(PI);
		for (int i = 0; i < 40; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI * 2 / 40 * i;
			dat.v = 7;
			dat.id = 1;
			dat.type = eBulletType::eBarrier;
			dat.color = eBulletColor::ePurple;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 40) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < IN_X + 20 || IN_X + IN_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 40) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = PI - b->dat.ang;
				b->dat.id = 2;
			}
		}
	}
}

void BarrageEasy::Barrage068() {

	if (_counter == 0) {
		_boss->setPos(OUT_W / 2, OUT_H / 2, 100);
	}

	if (_counter % 120 == 0) {
		_angle = GetRand(45)*PI2 / 360;
	}

	if (_counter % 5 == 0 && _counter % 120 < 10 && _counter >= 120) {
		bullet_t dat;
		for (int i = 0; i < 7; i++) {
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.v = 4;
			dat.id = 0;
			dat.ang = PI2 / 7 * i + _angle;
			dat.isAddBlend = true;
			dat.type = eBulletType::eUmaibo;
			dat.color = eBulletColor::eOrenge;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter >= 10)	b->dat.id = 1;
		}
		if (b->dat.id == 1) {
			b->dat.ang += PI / 60;
			if (b->dat.counter >= 150)	b->dat.id = 2;
		}
		if (b->dat.id == 2) {
			if (b->dat.x < 0 || b->dat.x>OUT_W || b->dat.y<0 || b->dat.y>OUT_H) {
				b->dat.ang += 3 * PI / 4 + GetRand(90)*PI2 / 360;
				b->dat.v = 1.8 + randf2(0.5);
				b->dat.id = 4;
				b->dat.color = eBulletColor::eYellow;
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}

}


void BarrageEasy::Barrage069() {

	if (_counter == 0) {

		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 0, 0, _launcherImage[0]));
		_launcher[0]->v = 1.3;
		_angle = 0;

		bullet_t dat;
		dat.x = _launcher[0]->x;
		dat.y = _launcher[0]->y;
		dat.ang = 0;
		dat.v = 0;
		dat.id = 0;
		dat.isAddBlend = true;
		dat.color = eBulletColor::eAqua;
		dat.type = eBulletType::eSparkBig;
		_list.push_back(new Bullet(&dat));

		SE::getIns()->setPlay(eSE::eSE_enemyShot);

	}

	if (_counter < Launcher::TIME)	return;

	_launcher[0]->ang = Calculator::getIns()->getAngleToPlayer(_launcher[0]->x, _launcher[0]->y);

	if (_counter % 12 == 0) {
		for (int i = 0; i < 2; i++) {
			bullet_t dat;
			dat.x = _launcher[0]->x;
			dat.y = _launcher[0]->y;
			dat.ang = _angle + i*PI2 / 2;
			dat.v = 0;
			dat.id = 1;
			dat.isAddBlend = true;
			dat.color = eBulletColor::ePink;
			dat.type = eBulletType::eKome;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
		_angle += PI / 15;
	}

	if (_counter % 90 == 0) {
		for (int i = 0; i < 4; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = _angle + i*PI2 / 4;
			dat.v = 3;
			dat.id = 2;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eUmaibo;
			_list.push_back(new Bullet(&dat));
		}
		for (int i = 0; i < 4; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = _angle + i*PI2 / 4;
			dat.v = 4;
			dat.id = 3;
			dat.color = eBulletColor::ePurple;
			dat.type = eBulletType::eUmaibo;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			b->dat.x = _launcher[0]->x;
			b->dat.y = _launcher[0]->y;
		}
		if (b->dat.id == 1) {
			b->dat.v += 0.03;
		}
		if (b->dat.id == 2) {
			b->dat.ang += PI / 360;
		}
		if (b->dat.id == 3) {
			b->dat.ang -= PI / 360;
		}
	}

}

void BarrageEasy::Barrage070() {
	if (_counter == 0)			_angle = -PI / 2;
	if (_counter % 120 == 0)	_boss->moveBit(150);

	if (_counter % 18 == 0) {
		for (int i = 0; i < 8; i++) {
			bullet_t dat;
			dat.x = _boss->getX() + 25 * cos(i*PI2 / 8);
			dat.y = _boss->getY() + 25 * sin(i*PI2 / 8);
			dat.ang = _angle;
			dat.v = 5;
			dat.id = 0;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eOfuda;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		_angle += PI / 3;
	}

	if (_counter % 120 == 0) {
		for (int i = 0; i < 16; i++) {
			bullet_t dat;
			dat.x = _boss->getX() + 75 * cos(i*PI2 / 16);
			dat.y = _boss->getY() + 75 * sin(i*PI2 / 16);
			dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() + PI / 4;
			dat.v = 5;
			dat.keepAlive = true;
			dat.id = 1;
			dat.color = eBulletColor::ePink;
			dat.type = eBulletType::eOfuda;
			_list.push_back(new Bullet(&dat));
		}
		for (int i = 0; i < 16; i++) {
			bullet_t dat;
			dat.x = _boss->getX() + 75 * cos(i*PI2 / 16);
			dat.y = _boss->getY() + 75 * sin(i*PI2 / 16);
			dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() - PI / 4;
			dat.v = 5;
			dat.keepAlive = true;
			dat.id = 1;
			dat.color = eBulletColor::ePink;
			dat.type = eBulletType::eOfuda;
			_list.push_back(new Bullet(&dat));
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 1) {
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				b->dat.keepAlive = false;
				b->dat.id = 2;
				b->dat.v = 2.5;
			}
		}
	}
}


void BarrageEasy::Barrage071() {

	if (_counter == 0) {
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = _boss->getX() - 200 + 200 * i;
			dat.y = -10;
			dat.v = 5;
			dat.id = 2 + i;
			dat.hit = false;
			dat.ang = PI / 2;
			dat.type = eBulletType::eSparkBig;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
		}
	}
	if (_counter < Launcher::TIME) {
		return;
	}
	if (_counter % 22 == 0) {
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = GetRand(OUT_W);
			dat.y = -10;
			dat.ang = PI / 2;
			dat.v = 2.5 + randf2(1.5);
			dat.id = 0;
			dat.hit = _counter % 600 < 300 ? true : false;
			dat.a = _counter % 600 < 300 ? 255 : 64;
			dat.type = eBulletType::eRing;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		for (int i = 0; i < 3; i++) {
			bullet_t dat;
			dat.x = GetRand(OUT_W);
			dat.y = OUT_H + 10;
			dat.ang = -PI / 2;
			dat.v = 2.5 + randf2(1.5);
			dat.id = 1;
			dat.hit = _counter % 600 < 300 ? false : true;
			dat.a = _counter % 600 < 300 ? 64 : 255;
			dat.type = eBulletType::eRing;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	for (auto b : _list) {
		if (b->dat.id >= 2) {
			if (b->dat.v > 0)	b->dat.v -= 0.1;
			if (b->dat.v < 0)	b->dat.v = 0;
			if (b->dat.id == 2) {
				if (_counter % 300 == 240) {
					b->dat.color = (b->dat.color + 1) % 2;
					SE::getIns()->setPlay(eSE::eSE_freeze);
				}
			}
			if (b->dat.id == 3) {
				if (_counter % 300 == 270) {
					b->dat.color = (b->dat.color + 1) % 2;
					SE::getIns()->setPlay(eSE::eSE_freeze);
				}
			}
			if (b->dat.id == 4) {
				if (_counter % 300 == 0) {
					b->dat.color = (b->dat.color + 1) % 2;
					SE::getIns()->setPlay(eSE::eSE_laser);
				}
			}
		}
		else if (_counter % 300 == 0 && _counter != 0) {
			if (_counter / 300 % 2 != 0) {
				b->dat.hit = (b->dat.id == 1 ? true : false);
				b->dat.a = (b->dat.id == 1 ? 255 : 64);
			}
			else {
				b->dat.hit = (b->dat.id == 0 ? true : false);
				b->dat.a = (b->dat.id == 0 ? 255 : 64);
			}
		}
	}
}

void BarrageEasy::Barrage072() {
	if (_counter == 0)			_angle = -PI / 2;
	if (_counter % 120 == 0)	_boss->moveBit(150);

	if (_counter % 10 == 0) {
		for (int i = 0; i < 70; i++) {
			bullet_t dat;
			dat.x = _boss->getX() + 125 * cos(i*PI2 / 70);
			dat.y = _boss->getY() + 125 * sin(i*PI2 / 70);
			dat.ang = _angle;
			dat.v = 5;
			dat.id = 0;
			dat.keepAlive = true;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eOfuda;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		_angle += PI / 6;
	}

	for (auto b : _list) {
		if (b->dat.counter > 120) {
			b->dat.keepAlive = false;
		}
		if (b->dat.id == 1) {
			if (b->dat.x < 20 || OUT_W - 20 < b->dat.x) {
				b->dat.ang = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				b->dat.keepAlive = false;
				b->dat.id = 2;
			}
		}
	}


}



void BarrageEasy::Barrage073() {
	const static int T = 800;
	const static int R = 380;
	if (_counter == 0 || _counter == T / 2) {
		_angle = 0;
		_launcher.push_back(new Launcher(CENTER_X, CENTER_Y - R, 0, 0, _launcherImage[0]));
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	for (Launcher* l : _launcher) {
		if (l->counter > Launcher::TIME) {
			int t = l->counter - Launcher::TIME;
			l->x = CENTER_X + cos(PI2 / T * t - PI / 2) * R;
			l->y = CENTER_Y + sin(PI2 / T * t - PI / 2) * R;
			if (l->counter % 30 == 0) {
				for (int i = 0; i < 5; i++) {
					bullet_t dat;
					dat.x = l->x;
					dat.y = l->y;
					dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) + PI2 / 5 * i;
					dat.id = 0;
					dat.v = 3.5;
					dat.type = eBulletType::eOfuda;
					dat.color = i == 0 ? eBulletColor::ePink : eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
				}
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}


// Ex Half-Sp1「弾幕開花宣言」


// Ex Boss-N3
void BarrageEasy::Barrage074() {

	double rangle;

	if (_counter % 50 == 0) {
		rangle = randf(PI);
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.x = _boss->getX() + 100 * cos(rangle + i*PI2 / 20);
			dat.y = _boss->getY() + 100 * sin(rangle + i*PI2 / 20);
			dat.v = 4;
			dat.id = 0;
			dat.ang = rangle + i*PI2 / 20 + PI;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	if ((_counter + 30) % 50 == 0) {
		rangle = randf(PI);
		for (int i = 0; i < 26; i++) {
			bullet_t dat;
			dat.x = _boss->getX() + 100 * cos(rangle + i*PI2 / 26);
			dat.y = _boss->getY() + 100 * sin(rangle + i*PI2 / 26);
			dat.v = 5;
			dat.id = 1;
			dat.ang = rangle + i*PI2 / 26 + PI;
			dat.type = eBulletType::eOfuda;
			dat.color = eBulletColor::ePurple;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	for (auto b : _list) {
		if (b->dat.id > 3)	continue;
		if (b->dat.id < 2) {
			b->dat.v -= 0.03;
			if (b->dat.v <= 0) {
				b->dat.v = 0;
				b->dat.counter = 0;
				b->dat.id += 2;
			}
		}
		else {
			if (b->dat.counter > 60) {
				b->dat.v = 3.5;
				b->dat.ang += (b->dat.id == 2 ? 1 : -1)*PI / 6;
				b->dat.id += 2;
			}
		}
	}

}

void BarrageEasy::Barrage075() {

	if (_counter % 180 == 0 && _counter != 0) {
		_boss->moveBit(150);
	}

	if (_counter % 30 == 0) {
		for (int i = 0; i < 12; i++) {	// 敵機外し型偶数弾
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() + PI2 / 12 * i + PI2 / 24;
			dat.v = 4.5;
			dat.id = 0;
			dat.color = _counter / 10 % 7;
			dat.type = eBulletType::eStar;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (_counter % 70<24 && _counter % 8 == 0) {
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() + PI2 / 20 * i;
			dat.v = 5.5;
			dat.id = 0;
			dat.color = i % eBulletColor::eColorNum;
			dat.type = eBulletType::eStar;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (_counter % 20 == 10) {
		for (int i = 0; i < 16; i++) {	// 自機狙い型偶数弾
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = Calculator::getIns()->getAngleFromBossToPlayer() + PI2 / 16 * i;
			dat.v = 5;
			dat.id = 0;
			dat.color = _counter / 10 % 7;
			dat.type = eBulletType::eStar;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

}

void BarrageEasy::Barrage076() {

	int t = _counter % 300;
	double rang;

	if (t % 10 == 0 && t<70 && t != 0) {
		for (int i = 0; i < 14; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.v = 6 - t / 20.0;
			dat.ang = i*PI2 / 14;
			dat.id = 0;
			dat.color = eBulletColor::eColorNum - 1 - t / 10;
			dat.type = eBulletType::eStar;
			dat.keepAlive = true;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (t % 60 == 0 && t >= 180) {
		rang = GetRand(180)* PI2 / 180;
		for (int i = 0; i < 8; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.v = 3;
			dat.ang = i*PI / 4 + rang;
			dat.id = 2;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eOdama;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	for (auto b : _list) {
		// 本体弾幕計算
		if (b->dat.id == 0) {
			if (b->dat.v > 0)	b->dat.v -= 0.02;
			else {
				b->dat.v = 0;
				b->dat.id = 1;
				b->dat.ang = b->dat.ang + PI;
				if (b->dat.color % 2 == 0)	b->dat.ang += PI / 72;
				else						b->dat.ang -= PI / 72;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.v < 4)	b->dat.v += 0.05;
			else				b->dat.keepAlive = false;
			if (b->dat.color % 2 == 0)	b->dat.ang += PI / 360;
			else						b->dat.ang -= PI / 360;
		}
	}

}


// Ex Boss-N4
void BarrageEasy::Barrage077() {

	double rangle;

	if (_counter % 270 == 0)	_angle = PI2 / 360 * GetRand(360);

	if (_counter % 5 == 0 && _counter % 270 < 90) {
		for (int i = 0; i < 36; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = _angle + PI2 / 36 * i;
			dat.v = 6;
			dat.id = 0;
			dat.color = i%eBulletColor::eColorNum;
			dat.type = eBulletType::eStar;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		_angle += PI / 180;
	}

	if (_counter % 270 == 210) {
		rangle = PI2 / 360 * GetRand(360);
		for (int i = 0; i < 16; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = rangle + PI2 / 16 * i;
			dat.v = 8;
			dat.id = 1;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eOdama;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	if (_counter % 270 == 240) {
		rangle = PI2 / 360 * GetRand(360);
		for (int i = 0; i < 16; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = rangle + PI2 / 16 * i;
			dat.v = 6;
			dat.id = 1;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eOdama;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	for (auto b : _list) {
		if (b->dat.id == 0)	b->dat.v += 0.02;
		if (b->dat.id == 1 && b->dat.v>3) {
			b->dat.v -= 0.05;
		}
	}

}

// Ex４：真夏の流星群
void BarrageEasy::Barrage078() {
	if (_counter % 20 == 0 && _counter % 240 <= 120) {
		for (int i = 0; i < 8; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = PI2 / 8 * i;
			dat.v = 6;
			dat.id = 0;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eOdama;
			_list.push_back(new Bullet(&dat));
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	int tern = _counter / 240;
	int t = _counter % 240;
	if (tern % 2) {
		if (_counter % 10 == 0) {
			for (int i = 0; i < 1; i++) {
				bullet_t dat;
				// ヨコ
				dat.x = 0;
				dat.y = GetRand(OUT_H);
				dat.ang = 0;
				dat.v = 2 + randf(1);
				dat.id = 1;
				dat.color = eBulletColor::eBlue;
				dat.type = eBulletType::eStar;
				_list.push_back(new Bullet(&dat));
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	else {
		if (_counter % 10 == 0) {
			for (int i = 0; i < 1; i++) {
				bullet_t dat;
				// ヨコ
				dat.x = OUT_W;
				dat.y = GetRand(OUT_H);
				dat.ang = PI;
				dat.v = 2 + randf(1);
				dat.id = 1;
				dat.color = eBulletColor::eYellow;
				dat.type = eBulletType::eStar;
				_list.push_back(new Bullet(&dat));
			}
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 1) {
			if (b->dat.counter > 120) {
				b->dat.v += 0.1;
			}
		}
		if (b->dat.id == 0) {
			if (b->dat.counter == 30) {
				Laser* laser = new Laser();
				laser->color = eLaserColor_Blue;
				laser->angle = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
				laser->startpt.x = b->dat.x;
				laser->startpt.y = b->dat.y;
				laser->counter = 0;
				laser->width = 1;
				laser->id = 5;
				laser->length = 1300;
				laser->hitWidth = 0;
				_boss->registLaser(laser);
				SE::getIns()->setPlay(eSE_laser);
				b->dat.hit = false;
				b->dat.a = 0;
			}

		}
	}

	list<Laser*> *laserlist = _boss->getLaserList();
	for (auto l : *laserlist) {
		if (l->counter >= 10 && l->counter <= 50) {
			l->width += 1;
		}
		if (l->counter == 60) {
			l->hitWidth = 1;
		}
		if (l->counter >= 140) {
			l->hitWidth = 0;
			l->width -= 4;
			if (l->width <= 0)	l->isAlive = false;
		}
	}
}








// Ex８「１２星座宇宙旅行〜space journy」
void BarrageEasy::Barrage079() {

	if (_counter == 0) {
		float h = OUT_H * 5 / 6 - 20;
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +OUT_W / 2 - 20, h, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -OUT_W / 2 + 20, h, _launcherImage[0]));
		_angle = 0;
	}

	double rangle;

	if (_counter % 32 == 0) {
		for (int i = 0; i < 2; i++) {
			bullet_t dat;
			dat.x = GetRand(OUT_W);
			dat.y = _boss->getY() + 50;
			dat.ang = -PI / 2;
			dat.v = 4;
			dat.a = 128;
			dat.id = 0;
			dat.color = eBulletColor::eBlue;
			dat.type = eBulletType::eStar;
			dat.hit = false;
			dat.isAlive = true;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
		}
	}

	if (_counter>240 && _counter % 340 == 0) {
		bullet_t dat;

		dat.x = _launcher.at(0)->x;
		dat.y = _launcher.at(0)->y;
		dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
		dat.v = 3.0;
		dat.id = 10;
		dat.color = eBulletColor::eBlue;
		dat.type = eBulletType::eOdama;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_enemyShot);

	}

	if (_counter>240 && _counter % 340 == 170) {
		bullet_t dat;

		dat.x = _launcher.at(1)->x;
		dat.y = _launcher.at(1)->y;
		dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
		dat.v = 3.0;
		dat.id = 10;
		dat.color = eBulletColor::eBlue;
		dat.type = eBulletType::eOdama;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			b->dat.v -= 0.02;
			if (b->dat.y <= -10) {
				b->dat.y = -10;
				b->dat.v = 0;
				b->dat.id = 1;
				b->dat.counter = 0;
			}
		}
		if (b->dat.id == 1 && b->dat.counter >= 120) {
			b->dat.ang = PI / 2;
			b->dat.v = 3.8 + randf(1.7);
			b->dat.id = 2;
			b->dat.a = 255;
			b->dat.hit = true;
			for (int i = 1; i < 6; i++) {
				bullet_t bul;
				bul = b->dat;
				bul.v -= i;
				_list.push_back(new Bullet(&bul));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
		if (b->dat.id == 10) {
			for (auto bb : _list) {
				if (bb->dat.id == 2) {
					float w = b->dat.x - bb->dat.x;
					float h = b->dat.y - bb->dat.y;
					if (w*w + h*h < 50 * 50) {
						bb->dat.ang = randf2(PI);
						bb->dat.id = 3;
						bb->dat.color = eBulletColor::ePink;
						bb->dat.v = 2.5 + randf2(0.8);
						SE::getIns()->setPlay(eSE::eSE_odamaCollision);
					}
				}
			}
		}
	}
}

void BarrageEasy::Barrage080() {
	if (_counter == 0) {
		_boss->setPos(_boss->getDefaultX(), _boss->getDefaultY() + 200, 40);
		_boss->setTime(99 * 60);
	}
	if (_boss->getResidualHp() > 75) {
		if (_counter % 400 == 40 || _counter % 400 == 200 + 40) {
			bool isBlue = ((_counter % 360) == 40) ? true : false;
			float angle = -PI / 2 + randf2(PI / 2);
			for (int i = 0; i < 150; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 150 * i * (isBlue ? 1 : -1);
				dat.id = isBlue ? 0 : 1;
				dat.v = 5;
				dat.keepAlive = true;
				dat.isAddBlend = true;
				dat.counter2 = isBlue ? i : -i;
				dat.type = eBulletType::eTama;
				dat.color = isBlue ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	else if (_boss->getResidualHp()>50) {
		if (_n == 0) {
			for (auto b : _list) {
				b->dat.kill = true;
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
			}
			_n = 1;
		}
		if (_counter % 380 == 0 || _counter % 380 == 190) {
			bool isBlue = ((_counter % 300) == 0) ? true : false;
			float angle = -PI / 2 + randf2(PI / 4);
			for (int i = 0; i < 150; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 150 * i * (isBlue ? 1 : -1);
				dat.id = dat.id = isBlue ? 2 : 3;
				dat.v = 5;
				dat.isAddBlend = true;
				dat.keepAlive = true;
				dat.counter2 = isBlue ? i : -i;
				dat.type = eBulletType::eTama;
				dat.color = isBlue ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	else if (_boss->getResidualHp() > 25) {
		if (_n == 1) {
			for (auto b : _list) {
				b->dat.kill = true;
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
			}
			_n = 2;
		}
		if (_counter % 200 == 0 || _counter % 200 == 100) {
			bool isBlue = ((_counter % 200) == 0) ? true : false;
			float angle = -PI / 2 + randf2(PI / 8);
			for (int i = 0; i < 150; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 150 * i * (isBlue ? 1 : -1);
				dat.id = dat.id = isBlue ? 4 : 5;
				dat.v = 5;
				dat.isAddBlend = true;
				dat.keepAlive = true;
				dat.counter2 = isBlue ? i : -i;
				dat.type = eBulletType::eTama;
				dat.color = isBlue ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	else {
		if (_n == 2) {
			for (auto b : _list) {
				b->dat.kill = true;
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
			}
			_n = 3;
		}
		if (_counter % 80 == 0 || _counter % 80 == 40) {
			bool isBlue = ((_counter % 80) == 0) ? true : false;
			float angle = -PI / 2 + randf2(PI / 4);
			for (int i = 0; i < 150; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 150 * i * (isBlue ? 1 : -1);
				dat.id = dat.id = isBlue ? 6 : 7;
				dat.v = 7.5;
				dat.isAddBlend = true;
				dat.keepAlive = true;
				dat.counter2 = isBlue ? i : -i;
				dat.type = eBulletType::eTama;
				dat.color = isBlue ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.05f;
			}
			if (0 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < 35) {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			else {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			b->dat.counter2++;
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.05f;
			}
			if (-35 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < 0) {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			else {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			b->dat.counter2--;
		}
		if (b->dat.id == 2) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.052f;
			}
			if (0 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < 20 || 60 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < 80) {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			else {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			b->dat.counter2++;
		}
		if (b->dat.id == 3) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.052f;
			}
			if (-20 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < 0 || -80 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < -60) {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			else {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			b->dat.counter2--;
		}
		if (b->dat.id == 4) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.053f;
			}
			bool isAvailable = true;
			for (int i = 0; i < 10; i++) {
				if (15 * i <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < 15 * i + 9) {
					isAvailable = false;
				}
			}
			if (isAvailable) {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			else {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			if (_counter % 10 == 0) {
				b->dat.counter2++;
			}
		}
		if (b->dat.id == 5) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.053f;
			}
			bool isAvailable = true;
			for (int i = 0; i < 10; i++) {
				if (-150 / 10 * i - 9 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < -150 / 10 * i) {
					isAvailable = false;
				}
			}
			if (isAvailable) {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			else {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			if (_counter % 10 == 0) {
				b->dat.counter2--;
			}
		}
		if (b->dat.id == 6) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.053f;
			}
			bool isAvailable = true;
			for (int i = 0; i < 10; i++) {
				if (15 * i <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < 15 * i + 9) {
					isAvailable = false;
				}
			}
			if (isAvailable) {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			else {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			if (_counter % 5 == 0) {
				b->dat.counter2++;
			}
		}
		if (b->dat.id == 7) {
			if (b->dat.counter < 80) {
				b->dat.v -= 0.053f;
			}
			bool isAvailable = true;
			for (int i = 0; i < 10; i++) {
				if (-150 / 10 * i - 9 <= b->dat.counter2 % 150 && b->dat.counter2 % 150 < -150 / 10 * i) {
					isAvailable = false;
				}
			}
			if (isAvailable) {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			else {
				b->dat.a = 10;
				b->dat.hit = false;
			}
			if (_counter % 5 == 0) {
				b->dat.counter2--;
			}
		}
		if (!(0 <= b->dat.x && b->dat.x <= OUT_W && 0 <= b->dat.y && b->dat.y <= OUT_H)) {
			b->dat.keepAlive = false;
		}
	}

}
