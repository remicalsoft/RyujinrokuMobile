#include "Define.h"
#include <math.h>
#include "BarrageNormal.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "ImageBullet.h"
#include "Utils.h"

using namespace std;

/********** 4面 **********/

void BarrageNormal::Barrage027()
{
	if (_counter % 50 == 0) {
		_boss->moveBit(60);
	}
	for (int t = 0; t < 3; t++) {
		if (_counter % 360 == 0 + 50 * t || _counter % 360 == 5 + 50 * t || _counter % 360 == 10 + 50 * t) {
			for (int j = 0; j < 6; j++) {
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 30 * 4 + PI / 30 * i + PI2 / 6 * j;
					dat.id = 0;
					dat.v = 4 + i;
					dat.type = eBulletType::eStar;
					dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
		if (_counter % 360 == 180 + 50 * t || _counter % 360 == 185 + 50 * t || _counter % 360 == 190 + 50 * t) {
			for (int j = 0; j < 6; j++) {
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 30 * 4 + PI / 30 * i + PI2 / 6 * j;
					dat.id = 0;
					dat.v = 10 - i;
					dat.type = eBulletType::eStar;
					dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
	}
}

void BarrageNormal::Barrage028()
{
	if (_counter % 240 == 0) {
		_boss->moveBit(50);
	}

	int t = _counter % 600;
	if (t == 0) {
		for (int i = 0; i <= 4; i++) {
			Laser* laser = new Laser();
			laser->color = eLaserColor_Blue;
			laser->angle = PI / 2;
			laser->startpt.x = IN_X + IN_W / 4 * i;
			laser->startpt.y = 0;
			laser->counter = 0;
			laser->width = 1;
			laser->id = 0;
			laser->length = 1300;
			laser->hitWidth = 0;
			_boss->registLaser(laser);
			SE::getIns()->setPlay(eSE_laser);
		}
	}
	if (t == 200) {
		for (int i = 0; i < 2; i++) {
			Laser* laser = new Laser();
			laser->color = eLaserColor_Blue;
			laser->angle = PI / 2;
			laser->startpt.x = IN_X + IN_W * i;
			laser->startpt.y = 0;
			laser->counter = 0;
			laser->width = 1;
			laser->id = 0;
			laser->length = 1300;
			laser->hitWidth = 0;
			_boss->registLaser(laser);
			SE::getIns()->setPlay(eSE_laser);
		}
		{
			Laser* laser = new Laser();
			laser->color = eLaserColor_Blue;
			laser->angle = PI*0.74;
			laser->startpt.x = OUT_W;
			laser->startpt.y = 0;
			laser->counter = 0;
			laser->width = 1;
			laser->id = 0;
			laser->length = 1300;
			laser->hitWidth = 0;
			_boss->registLaser(laser);
			SE::getIns()->setPlay(eSE_laser);
		}
		{
			Laser* laser = new Laser();
			laser->color = eLaserColor_Blue;
			laser->angle = PI*0.26;
			laser->startpt.x = 0;
			laser->startpt.y = 0;
			laser->counter = 0;
			laser->width = 1;
			laser->id = 0;
			laser->length = 1300;
			laser->hitWidth = 0;
			_boss->registLaser(laser);
			SE::getIns()->setPlay(eSE_laser);
		}
	}
	if (t == 400) {
		for (int i = 0; i <= 4; i += 2) {
			Laser* laser = new Laser();
			laser->color = eLaserColor_Blue;
			laser->angle = 0;
			laser->startpt.x = 0;
			laser->startpt.y = IN_Y + IN_H / 4 * i;
			laser->counter = 0;
			laser->width = 1;
			laser->id = 0;
			laser->length = 1300;
			laser->hitWidth = 0;
			_boss->registLaser(laser);
			SE::getIns()->setPlay(eSE_laser);
		}
		for (int i = 1; i <= 4; i += 2) {
			Laser* laser = new Laser();
			laser->color = eLaserColor_Blue;
			laser->angle = PI;
			laser->startpt.x = IN_X + IN_W;
			laser->startpt.y = IN_Y + IN_H / 4 * i;
			laser->counter = 0;
			laser->width = 1;
			laser->id = 0;
			laser->length = 1300;
			laser->hitWidth = 0;
			_boss->registLaser(laser);
			SE::getIns()->setPlay(eSE_laser);
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (60 < b->dat.counter && b->dat.counter< 100) {
				b->dat.v += 0.03;
			}
		}
	}

	list<Laser*> *laserList = _boss->getLaserList();
	for (auto l : *laserList) {
		int cnt = l->counter;
		int id = l->id;
		if (id == 0) {
			if (60 <= cnt&&cnt <= 80) {
				l->width = (cnt - 60) * 2;
			}
			if (cnt == 80) {
				l->width = 40;
				l->hitWidth = 0.6;
			}
			if (80 <= cnt && cnt <= 180 && cnt % 2) {
				int t = cnt - 80;
				{
					bullet_t dat;
					dat.x = l->startpt.x + cos(l->angle)*l->length*t / 100;
					dat.y = l->startpt.y + sin(l->angle)*l->length*t / 100;
					dat.ang = randf2(PI);
					dat.v = 0;
					dat.id = 0;
					dat.type = eBulletType::eStar;
					dat.color = GetRand(eBulletColor::eColorNum - 1);
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
			if (cnt >= 180 && cnt <= 220) {
				if (cnt == 180) {
					l->hitWidth = 0;
				}
				l->width = 40 - 40 * ((cnt - 180) / 40.0);
				if (cnt == 220) {
					l->isAlive = false;
				}
			}
		}
	}

}

void BarrageNormal::Barrage029()
{
	if (_counter % 120 == 0) {
		_boss->moveBit(50);
	}
	for (int t = 0; t < 3; t++) {
		if (_counter % 180 == 0) {
			_baseAngle[0] = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		}
		if (_counter % 360 == 0 + 50 * t || _counter % 360 == 3 + 50 * t || _counter % 360 == 6 + 50 * t) {
			for (int j = 0; j < 17; j++) {
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = _baseAngle[0] - PI / 11 * 4 + PI / 11 * i + PI2*0.117* j;
					dat.id = 0;
					dat.v = 3 + 0.47*i;
					dat.type = eBulletType::eStar;
					dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
		if (_counter % 360 == 180 + 50 * t || _counter % 360 == 183 + 50 * t || _counter % 360 == 186 + 50 * t) {
			for (int j = 0; j < 17; j++) {
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = _baseAngle[0] - PI / 11 * 4 + PI / 11 * i + PI2*0.117 * j;
					dat.id = 0;
					dat.v = 8 - 0.26*i;
					dat.type = eBulletType::eStar;
					dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
	}
}

void BarrageNormal::Barrage030()
{
	if ((_counter % 400) == 400 - 60) {
		_boss->moveBitMiddle(30);
	}

	if (_counter % 15 == 0 && _counter % 400 <= 240) {
		float angle = Calculator::getIns()->getAngleFromBossToPlayer();
		Laser* laser = new Laser();
		laser->color = eLaserColor_Blue;
		laser->angle = angle - PI2 / 3;
		laser->startpt.x = _boss->getX() + cos(laser->angle) * 100;
		laser->startpt.y = _boss->getY() + sin(laser->angle) * 100;
		laser->counter = 0;
		laser->width = 1;
		laser->id = 0;
		laser->length = 950;
		laser->hitWidth = 0;

		laser->lphy.conv_flag = 1;
		laser->lphy.conv_base_x = _boss->getX();
		laser->lphy.conv_base_y = _boss->getY();
		laser->lphy.conv_x = laser->startpt.x;
		laser->lphy.conv_y = laser->startpt.y;
		laser->lphy.angle = PI2 / 3;
		laser->lphy.base_ang = laser->angle;
		laser->lphy.time = 40;

		SE::getIns()->setPlay(eSE_laser);
		_boss->registLaser(laser);
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (60 < b->dat.counter && b->dat.counter< 100) {
				b->dat.v += 0.03;
			}
		}
	}

	list<Laser*> *laserList = _boss->getLaserList();
	for (auto l : *laserList) {
		int t = _counter % 400;
		int cnt = l->counter;
		int id = l->id;
		if (id == 0) {
			if (60 <= cnt&&cnt <= 80) {
				l->width = (cnt - 60);
			}
			if (cnt == 80) {
				l->width = 20;
				l->hitWidth = 0.6;
			}
			if (t == 320) {
				for (int i = 0; i < 50; i++) {
					bullet_t dat;
					dat.x = l->startpt.x + cos(l->angle)*l->length*i / 50;
					dat.y = l->startpt.y + sin(l->angle)*l->length*i / 50;
					dat.ang = randf2(PI);
					dat.v = 0;
					dat.id = 0;
					dat.isAddBlend = true;
					dat.type = eBulletType::eStar;
					dat.color = GetRand(eBulletColor::eColorNum - 1);
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
			if (t >= 320 && cnt <= 360) {
				if (t == 320) {
					l->hitWidth = 0;
				}
				l->width = 20 - 20 * ((t - 320) / 40.0);
				if (t == 360) {
					l->isAlive = false;
				}
			}
		}
	}
}

void BarrageNormal::Barrage031()
{
	if (_counter % 120 == 0) {
		_boss->moveBit(50);
	}
	for (int t = 0; t < 3; t++) {
		if (_counter % 180 == 0) {
			_baseAngle[0] = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		}
		if (_counter % 360 == 0 + 50 * t || _counter % 360 == 5 + 50 * t || _counter % 360 == 10 + 50 * t || _counter % 360 == 15 + 50 * t || _counter % 360 == 20 + 50 * t) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = _baseAngle[0] - PI / 20 * 4 + PI / 20 * i + PI2 / 4 * j;
					dat.id = 0;
					dat.v = 3 + 0.47*i;
					dat.type = eBulletType::eStar;
					dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
		if (_counter % 360 == 0 || _counter % 360 == 180) {
			for (int j = 0; j < 6; j++) {
				for (int i = 0; i < 16; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = _baseAngle[0] - PI2 / 16 * i;
					dat.id = 0;
					dat.v = 4 + j;
					dat.type = eBulletType::eOdama;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
		if (_counter % 360 == 180 + 50 * t || _counter % 360 == 185 + 50 * t || _counter % 360 == 190 + 50 * t || _counter % 360 == 195 + 50 * t || _counter % 360 == 200 + 50 * t) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = _baseAngle[0] - PI / 20 * 4 + PI / 20 * i + PI2 / 4 * j;
					dat.id = 0;
					dat.v = 8 - 0.26*i;
					dat.type = eBulletType::eStar;
					dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
	}

}

void BarrageNormal::Barrage032()
{
	if (_counter % 50 == 0) {
		float angle = randf2(PI);
		for (int j = 0; j < 15; j++) {
			int color = GetRand(eBulletColor::eColorNum - 1);
			for (int i = 0; i < 9; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI / 150 * i + PI2 / 15 * j;
				dat.id = 0;
				dat.v = 0.8 + 10;
				dat.a = 64;
				dat.type = eBulletType::eStar;
				dat.color = color;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	if (_boss->getResidualHp() < 60 && _counter % 40 == 20) {
		float angle = randf2(PI);
		for (int j = 0; j < 10; j++) {
			int color = GetRand(eBulletColor::eColorNum - 1);
			for (int i = 0; i < 9; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = angle + PI / 150 * i + PI2 / 10 * j;
				dat.id = 0;
				dat.a = 64;
				dat.v = 0.8 + 10;
				dat.type = eBulletType::eStar;
				dat.color = color;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	if (_boss->getResidualHp() < 60 && _counter % 180 == 0) {
		float angle = Calculator::getIns()->getAngleFromBossToPlayer();
		for (int i = 0; i < 10; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI2 / 10 * i;
			dat.id = 1;
			dat.v = 2.5;
			dat.type = eBulletType::eOdama;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
		}
	}
	const static float R = 54;
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter< 50) {
				b->dat.v -= 0.2;
			}
			if (b->dat.counter == 50) {
				b->dat.a = 255;
			}
		}
		if (b->dat.id == 1) {
			for (auto b2 : _list) {
				if (b2->dat.id == 0 && b2->dat.counter>50) {
					float w = b->dat.x - b2->dat.x;
					float h = b->dat.y - b2->dat.y;
					if (w*w + h*h < R*R) {
						b2->dat.id = 2;
						b2->dat.v *= 2;
						b2->dat.ang = randf2(PI);
					}
				}
			}
		}
	}
}

void BarrageNormal::Barrage033()
{
	if (_counter % 120 == 0) {
		_boss->moveBit(60);
	}
	if (_counter % 240<120 && _counter % 10 == 0) {
		int t = _counter % 240;
		float angle = Calculator::getIns()->getAngleToPlayer(_boss->getX(), _boss->getY());
		for (int i = 0; i < 30; i++) {
			for (int v = 0; v < 2; v++) {
				bullet_t dat;
				dat.x = _boss->getX() - 300 + 600 / 120.f*t;
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 30 * i;
				dat.id = 0;
				dat.v = 4 + v;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 180) {
				b->dat.keepAlive = false;
			}
		}
	}
}

void BarrageNormal::Barrage034()
{
	if (_counter == 0) {
		_boss->setPos(_boss->getX(), _boss->getY() + 150, 50);
	}
	for (int i = 0; i < 6; i++) {
		if (_remValue[i] <= 0) {
			_remValue[i]--;
		}
		else {
			_remValue[i]++;
		}
	}

	if (_boss->getResidualHp() >= 60) {
		for (int i = 0; i < 6; i++) {
			if (_remValue[i] <= -35) {
				if (GetRand(15) == 0) {
					_remValue[i] = 1;
				}
			}
			if (_remValue[i] <= -50) {
				_remValue[i] = 1;
			}
			if (_remValue[i] > 10) {
				if (GetRand(15) == 0) {
					_remValue[i] = 0;
				}
			}
			if (_remValue[i] > 35) {
				_remValue[i] = 0;
			}
		}
		if (_counter > 50 && _counter % 1 == 0) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.ang = PI2 / 4 * i + PI2 / 900 * _counter;
				dat.x = _boss->getX() + cos(dat.ang) * 800;
				dat.y = _boss->getY() + sin(dat.ang) * 800;
				dat.id = 0;
				dat.v = -2.5;
				if (_remValue[i] > 0) {
					dat.a = 255;
				}
				else {
					dat.a = 24;
					dat.hit = false;
				}
				dat.keepAlive = true;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
		if (_counter > 50 && _counter % 1 == 0) {
			for (int i = 2; i < 6; i++) {
				bullet_t dat;
				dat.ang = PI2 / 4 * i - PI2 / 900 * _counter;
				dat.x = _boss->getX() + cos(dat.ang) * 800;
				dat.y = _boss->getY() + sin(dat.ang) * 800;
				dat.id = 0;
				dat.v = -2.5;
				if (_remValue[i] > 0) {
					dat.a = 255;
				}
				else {
					dat.a = 24;
					dat.hit = false;
				}
				dat.keepAlive = true;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	else {
		if (_isDone == false) {
			for (auto b : _list) {
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
				delete b;
			}
			_list.clear();
			_isDone = true;
		}
		for (int i = 0; i < 6; i++) {
			if (_remValue[i] <= -30) {
				if (GetRand(15) == 0) {
					_remValue[i] = 1;
				}
			}
			if (_remValue[i] > 20) {
				if (GetRand(20) == 0) {
					_remValue[i] = 0;
				}
			}
			if (_remValue[i] > 46) {
				_remValue[i] = 0;
			}
		}
		if (_counter % 2 == 0) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.ang = PI2 / 4 * i + PI2 / 477 * _counter;
				dat.x = _boss->getX() + cos(dat.ang) * 800;
				dat.y = _boss->getY() + sin(dat.ang) * 800;
				dat.id = 1;
				dat.v = -6.5;
				if (_remValue[i] > 0) {
					dat.a = 255;
				}
				else {
					dat.a = 24;
					dat.hit = false;
				}
				dat.keepAlive = true;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
			for (int i = 3; i < 6; i++) {
				bullet_t dat;
				dat.ang = PI2 / 3 * i - PI2 / 637 * _counter;
				dat.x = _boss->getX() + cos(dat.ang) * 800;
				dat.y = _boss->getY() + sin(dat.ang) * 800;
				dat.id = 1;
				dat.v = -6.5;
				if (_remValue[i] > 0) {
					dat.a = 255;
				}
				else {
					dat.a = 24;
					dat.hit = false;
				}
				dat.keepAlive = true;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
		{
			if (_boss->getResidualHp() < 35 && _counter % 30 == 0) {
				for (int i = 0; i < 12; i++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = PI2 / 13 * i + randf2(PI2 / 20);
					dat.id = 4;
					dat.v = 2.5 + randf2(1);
					dat.type = eBulletType::eKome;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
	float R = 40;
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter< 40) {
				b->dat.v -= 0.2;
			}
			if (b->dat.counter == 180) {
				b->dat.keepAlive = false;
			}
			float w = b->dat.x - _boss->getX();
			float h = b->dat.y - _boss->getY();
			if (w*w + h*h < R*R) {
				b->dat.isAlive = false;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter == 120) {
				b->dat.keepAlive = false;
			}
			float w = b->dat.x - _boss->getX();
			float h = b->dat.y - _boss->getY();
			if (w*w + h*h < R*R) {
				b->dat.isAlive = false;
			}
		}
	}
}

void BarrageNormal::Barrage035()
{
	if (_counter % 100 == 0) {
		_boss->moveBit(60);
	}
	if (_counter % 240<100 && _counter % 11 == 0) {
		int t = _counter % 240;
		float angle = randf2(PI / 30);
		for (int i = 0; i < 20; i++) {
			for (int v = 0; v < 2; v++) {
				bullet_t dat;
				dat.x = _boss->getX() - 300 + 300 * t / 100;
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 20 * i;
				dat.id = 0;
				dat.keepAlive = true;
				dat.v = 4 + v;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	if (100 <= _counter % 240 && _counter % 240<200 && _counter % 11 == 0) {
		int t = _counter % 240 - 100;
		float angle = randf2(PI / 30);
		for (int i = 0; i < 20; i++) {
			for (int v = 0; v < 2; v++) {
				bullet_t dat;
				dat.x = _boss->getX() + 300 - 300 * t / 100;
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 20 * i;
				dat.id = 0;
				dat.keepAlive = true;
				dat.v = 4 + v;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 240) {
				b->dat.keepAlive = false;
			}
		}
	}
}

void BarrageNormal::Barrage036()
{
	if (_counter % 240 == 0) {
		_boss->moveBit(50);
	}
	if (_counter % 50 == 0) {
		for (int j = 0; j < 10; j++) {
			float v = 9 + randf2(0.5);
			float ang = randf2(PI2 / 20);
			for (int i = 0; i < 50; i++) {
				bullet_t dat;
				dat.x = _boss->getX() + cos(PI2 / 50 * i) * 100;
				dat.y = _boss->getY() + sin(PI2 / 50 * i) * 100;
				dat.ang = PI2 / 10 * j + ang;
				dat.id = i;
				dat.v = v;
				dat.a = 24;
				dat.hit = false;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id < 100) {
			if (b->dat.counter<75) {
				b->dat.v -= 0.1f;
			}
			if (b->dat.counter % 150 == (b->dat.id * 3) % 150) {
				b->dat.a = 255;
				b->dat.hit = true;
			}
			if (b->dat.counter % 150 == (b->dat.id * 3 + 35) % 150) {
				b->dat.a = 24;
				b->dat.hit = false;
			}
		}
	}
}

void BarrageNormal::Barrage037()
{
	if (_counter % 120 == 0) {
		_boss->moveBit(50);
	}
	if (_counter % 240<120 && _counter % 8 == 0) {
		float angle = randf2(PI / 30);
		for (int i = 0; i < 20; i++) {
			for (int v = 0; v < 2; v++) {
				bullet_t dat;
				dat.x = 448 + randf2(400);
				dat.y = _boss->getY();
				dat.ang = angle + PI2 / 20 * i;
				dat.id = 0;
				dat.v = 11 + v;
				dat.type = eBulletType::eStar;
				dat.color = eBulletColor::eBlue + i%eBulletColor::eColorNum;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter<100) {
				b->dat.v -= 0.1;
			}
		}
	}

}

void BarrageNormal::Barrage038()
{
	if (_counter == 0) {
		int TIME = 60 * 60;
		_boss->setTime(TIME);
		_boss->setSpellMAXTime(TIME);
	}
	if (_counter % 1200 == 1199) {
		_n++;
	}
	if (_n <= 2) {
		if (_counter % 1200 < 400 && _counter % 2 == 0) {
			if (_counter % 1200 == 0) {
				SE::getIns()->setPlay(eSE::eSE_rain);
			}
			{
				bullet_t dat;
				dat.x = GetRand(OUT_W);
				dat.y = -20;
				dat.ang = PI*0.6;
				dat.id = 0;
				dat.v = 9 + randf2(3);
				dat.keepAlive = true;
				dat.type = eBulletType::eRain;
				dat.color = eBulletColor::eAqua;
				_list.push_back(new Bullet(&dat));
			}
			{
				bullet_t dat;
				dat.x = OUT_W + 20;
				dat.y = GetRand(OUT_H);
				dat.ang = PI*0.6;
				dat.id = 0;
				dat.v = 9 + randf2(3);
				dat.keepAlive = true;
				dat.type = eBulletType::eRain;
				dat.color = eBulletColor::eAqua;
				_list.push_back(new Bullet(&dat));
			}
		}
		if (_counter % 1200 == 400) {
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 20 + 16 * 0 - _boss->getX(), WIN_H - 20 - _boss->getY(), _launcherImage[0]));
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 20 + 16 * 1 - _boss->getX(), WIN_H - 20 - _boss->getY(), _launcherImage[0]));
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 20 + 16 * 2 - _boss->getX(), WIN_H - 20 - _boss->getY(), _launcherImage[0]));
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 20 + 16 * 3 - _boss->getX(), WIN_H - 20 - _boss->getY(), _launcherImage[0]));
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 20 + 16 * 4 - _boss->getX(), WIN_H - 20 - _boss->getY(), _launcherImage[0]));
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 20 + 16 * 5 - _boss->getX(), WIN_H - 20 - _boss->getY(), _launcherImage[0]));
			_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), 20 + 16 * 6 - _boss->getX(), WIN_H - 20 - _boss->getY(), _launcherImage[0]));
		}
		if (_counter % 1200 == 460) {
			for (int i = 0; i < 7; i++) {
				_launcher[i]->ang = -PI / 2;
				_launcher[i]->v = 10 - 1.5 / 7.f*i;
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_rainbow);
		}
		for (auto l : _launcher) {
			l->ang += PI / 280;
			if (l->v != 0 && l->counter % 1 == 0) {
				bullet_t dat;
				dat.x = l->x;
				dat.y = l->y;
				dat.ang = l->ang;
				dat.id = 1+l->id;
				dat.v = 0;
				dat.keepAlive = true;
				dat.isAddBlend = true;
				dat.type = eBulletType::eRainbow;
				dat.color = l->id;
				_list.push_back(new Bullet(&dat));
			}
		}
		if (_counter % 1200 == 610) {
			for (auto l : _launcher) {
				delete l;
			}
			_launcher.clear();
		}
	}
	
	static const int color[] = {
		eBulletColor::ePink,
		eBulletColor::eOrenge,
		eBulletColor::eYellow,
		eBulletColor::eLime,
		eBulletColor::eAqua,
		eBulletColor::eBlue,
		eBulletColor::ePurple,
	};

	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 60) {
				b->dat.keepAlive = false;
			}
		}
		if (1<=b->dat.id && b->dat.id<10) {
			if (_n == 0 && _counter == 640) {
				//				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
				b->dat.keepAlive = false;
				b->dat.isAlive = false;
				{
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = randf2(PI);
					dat.id = 10;
					dat.v = 0;
					dat.val = 0.03 + randf2(0.01);
					dat.type = eBulletType::eStar;
					dat.color = color[b->dat.id - 1];
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
			if (_n == 1 && b->dat.counter == 90) {
				b->dat.keepAlive = false;
				b->dat.isAlive = false;
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = PI2 / 50 * _counter - PI*0.5 + PI2*i / 3;
					dat.id = 10;
					dat.v = 0;
					dat.val = 0.03;
					dat.type = eBulletType::eStar;
					dat.color = color[b->dat.id - 1];
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
			if (_n == 2 && b->dat.counter == 90) {
				b->dat.keepAlive = false;
				b->dat.isAlive = false;
				if (_counter % 1 == 0) {
					bullet_t dat;
					dat.x = b->dat.x;
					dat.y = b->dat.y;
					dat.ang = PI2 / 50 * _counter + PI2 / 30 * dat.x;
					dat.id = 10;
					dat.v = 0;
					dat.val = 0.03;
					dat.type = eBulletType::eStar;
					dat.color = color[b->dat.id - 1];
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
		if (b->dat.id == 10) {
			if (60 <= b->dat.counter && b->dat.counter<120) {
				b->dat.v += b->dat.val;
			}
			if (420 <= b->dat.counter) {
				b->dat.v += 0.01f;
			}
		}
	}
}
