#include "Define.h"
#include <math.h>
#include "BarrageHard.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "ImageBullet.h"
#include "Utils.h"

using namespace std;

/********** 5面 **********/

void BarrageHard::Barrage039()
{
	if (_counter % 400 <= 84 && _counter % 2 == 0) {
		int t = _counter % 400;
		if (t == 0) {
			_baseAngle[0] = randf2(PI);
		}
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.x = cos(PI*0.2)*t * 10;
			dat.y = sin(PI*0.2)*t * 10;
			dat.ang = PI2 / 20 * i + _baseAngle[0] + PI / 300 * t;
			dat.id = 0;
			dat.v = 7;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		_implBulletEffect->registBulletEffect(cos(PI*0.2)*t * 10, sin(PI*0.2)*t * 10, eBulletEffectType_Appear);
	}
	if (200 <= _counter % 400 && _counter % 400 <= 200 + 84 && _counter % 2 == 0) {
		int t = (_counter % 400) - 200;
		if (t == 0) {
			_baseAngle[0] = randf2(PI);
		}
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.x = OUT_W + cos(PI*0.8)*t * 10;
			dat.y = sin(PI*0.8)*t * 10;
			dat.ang = PI2 / 20 * i + _baseAngle[0] - PI / 300 * t;
			dat.id = 0;
			dat.v = 7;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		_implBulletEffect->registBulletEffect(OUT_W + cos(PI*0.8)*t * 10, sin(PI*0.8)*t * 10, eBulletEffectType_Appear);
	}
}

void BarrageHard::Barrage040()
{
	if (_counter == 0) {
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -300, -50, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +300, -50, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), -200, +50, _launcherImage[0]));
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), +200, +50, _launcherImage[0]));
	}
	if (_counter<60) {
		return;
	}
	if (_counter % 60 == 0) {
		for (int l = 0; l < 2; l++) {
			Launcher *p = _launcher[l];
			float ang = randf2(PI);
			for (int i = 0; i < 10; i++) {
				for (int s = 0; s < 40; s++) {
					bullet_t dat;
					dat.x = p->x;
					dat.y = p->y;
					dat.ang = ang + PI2 / 10 * i + PI2 / 900 * s;
					dat.id = 0;
					dat.isAddBlend = true;
					dat.v = l ? (5 + 1.f / 40 * s) : (6 - 1.f / 40 * s);
					dat.type = eBulletType::eAme;
					dat.color = l ? eBulletColor::eBlue : eBulletColor::ePink;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
	if (_boss->getResidualHp()<50) {
		if (_baseAngle[0] == 0 || _counter % 60 == 0) {
			_baseAngle[0] = Calculator::getIns()->getAngleToPlayer(_launcher[2]->x, _launcher[2]->y);
			_baseAngle[1] = Calculator::getIns()->getAngleToPlayer(_launcher[3]->x, _launcher[3]->y);
		}
		if (_counter % 60 < 10 && _counter % 1 == 0) {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < 20; i++) {
					bullet_t dat;
					dat.ang = _baseAngle[j] + PI2 / 20 * i;
					dat.x = _launcher[2 + j]->x;
					dat.y = _launcher[2 + j]->y;
					dat.v = 8;
					dat.id = 1;
					dat.isAddBlend = true;
					dat.type = eBulletType::eBarrier;
					dat.color = j ? eBulletColor::eBlue : eBulletColor::ePink;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
	}
}

/**中ボス2**/

void BarrageHard::Barrage041()
{
	if (_counter % 200 == 0) {
		_boss->moveBit(50);
	}

	if (_counter % 400 <= 120 && _counter % 2 == 0) {
		int t = _counter % 400;
		if (t == 0) {
			_baseAngle[0] = randf2(PI);
		}
		for (int i = 0; i < 26; i++) {
			bullet_t dat;
			dat.x = cos(PI*0.2)*t * 10;
			dat.y = sin(PI*0.2)*t * 10;
			dat.ang = PI2 / 26 * i + _baseAngle[0] + PI / 180 * t;
			dat.id = 0;
			dat.v = 4;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		_implBulletEffect->registBulletEffect(cos(PI*0.2)*t * 10, sin(PI*0.2)*t * 10, eBulletEffectType_Appear);
	}
	if (200 <= _counter % 400 && _counter % 400 <= 200 + 120 && _counter % 2 == 0) {
		int t = (_counter % 400) - 200;
		if (t == 0) {
			_baseAngle[0] = randf2(PI);
		}
		for (int i = 0; i < 26; i++) {
			bullet_t dat;
			dat.x = OUT_W + cos(PI*0.8)*t * 10;
			dat.y = sin(PI*0.8)*t * 10;
			dat.ang = PI2 / 26 * i + _baseAngle[0] - PI / 180 * t;
			dat.id = 0;
			dat.v = 4;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		_implBulletEffect->registBulletEffect(OUT_W + cos(PI*0.8)*t * 10, sin(PI*0.8)*t * 10, eBulletEffectType_Appear);
	}
}

void BarrageHard::Barrage042()
{
	if (_counter % 70 == 0) {
		Launcher *l = new Launcher(OUT_W, OUT_H - 16, _launcherImage[0]);
		l->ang = PI;
		l->v = 1.5;
		l->id = 0;
		l->isShooting = true;
		_launcher.push_back(l);
		SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
	}
	if (_boss->getResidualHp() <= 50) {
		if (_counter % 140 == 35) {
			Launcher *l = new Launcher(0, OUT_H - 16, _launcherImage[0]);
			l->ang = 0;
			l->v = 1.8;
			l->id = 1;
			l->isShooting = true;
			_launcher.push_back(l);
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto l : _launcher) {
		if (l->counter % 2 == 0) {
			if (l->isShooting) {
				l->shotCounter++;
			}
			else {
				l->shotCounter--;
			}
			if (l->shotCounter>3 || l->shotCounter<-3) {
				if (l->shotCounter>12 || l->shotCounter<-10 || GetRand(6) == 0) {
					l->isShooting = !l->isShooting;
					l->shotCounter = 0;
				}
			}
			bullet_t dat;
			dat.x = l->x;
			dat.y = l->y;
			dat.ang = -PI / 2;
			dat.id = 0;
			dat.v = l->id == 0 ? 6 : 9;
			dat.isAddBlend = true;
			dat.hit = l->isShooting;
			dat.a = dat.hit ? 255 : 16;
			dat.type = eBulletType::eSparkBig;
			dat.color = l->id == 0 ? eBulletColor::eBlue : eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
		}

	}

}

/** ボス **/

void BarrageHard::Barrage043()
{
	if (_counter % 200 == 0) {
		_boss->moveBit(50);
	}

	if (_counter % 300 <= 100 && _counter % 5 == 0) {
		int t = _counter % 300;
		if (t == 0) {
			_baseAngle[0] = randf2(PI);
		}
		for (int i = 0; i < 16; i++) {
			bullet_t dat;
			dat.x = cos(PI*0.2)*t * 10;
			dat.y = sin(PI*0.2)*t * 10;
			dat.ang = PI2 / 16 * i + _baseAngle[0] + PI / 90 * t;
			dat.id = 0;
			dat.v = 5;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::eBlue;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		_implBulletEffect->registBulletEffect(cos(PI*0.2)*t * 10, sin(PI*0.2)*t * 10, eBulletEffectType_Appear);
	}
	if (150 <= _counter % 300 && _counter % 300 <= 150 + 100 && _counter % 5 == 0) {
		int t = (_counter % 300) - 150;
		if (t == 0) {
			_baseAngle[0] = randf2(PI);
		}
		for (int i = 0; i < 16; i++) {
			bullet_t dat;
			dat.x = OUT_W + cos(PI*0.8)*t * 10;
			dat.y = sin(PI*0.8)*t * 10;
			dat.ang = PI2 / 16 * i + _baseAngle[0] - PI / 90 * t;
			dat.id = 0;
			dat.v = 5;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		_implBulletEffect->registBulletEffect(OUT_W + cos(PI*0.8)*t * 10, sin(PI*0.8)*t * 10, eBulletEffectType_Appear);
	}
}
/** スペル1 **/
void BarrageHard::Barrage044()
{
	if (_counter % 90 < 45 && _counter % 2 == 0) {
		if (_counter % 90 == 0) {
			_baseAngle[0] = Calculator::getIns()->getAngleFromBossToPlayer();
			_baseAngle[1] = randf2(PI);
		}
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 50; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = _baseAngle[1] + PI2 / 50 * i;
				dat.id = j;
				dat.v = 8.6;
				dat.isAddBlend = true;
				dat.type = eBulletType::eKome;
				dat.color = eBulletColor::eBlue + (j ? 2 : 0);
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
		if (_counter % 10 == 0 && _counter%90<40) {
			for (int i = 0; i < 30; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = _baseAngle[0] + PI2 / 30 * i;
				dat.id = 2;
				//				dat.isAddBlend = true;
				dat.v = 2;
				dat.type = eBulletType::eOdama;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0 || b->dat.id == 1) {
			if (b->dat.counter < 60) {
				b->dat.ang += PI2 / 120 * (b->dat.id ? -1 : 1);
			}
			if (110<b->dat.counter && b->dat.counter<110+40) {
				b->dat.v -= 0.2;
			}
		}
	}

}

void BarrageHard::Barrage045()
{
	const static int T = 60;
	if (_counter % 200 == 0) {
		_boss->moveBit(50);
	}
	for (int j = 0; j < 2; j++) {
		if ((T / 2)*j <= _counter % T && _counter % T <= (T / 2)*j + 20 && _counter % 1 == 0) {
			int t = _counter % (T / 2);
			if (t == 0) {
				_baseAngle[0] = randf2(PI);
			}
			for (int i = 0; i < 21; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI2 / 21 * i + _baseAngle[0] + PI / 250 * t*(j ? -1 : 1);
				dat.id = 0;
				dat.v = 4;
				dat.isAddBlend = true;
				dat.type = eBulletType::eKome;
				dat.color = j ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

/** スペル2 **/
void BarrageHard::Barrage046()
{
	if (_counter == 0) {
		for (int i = 0; i < 90; i++) {
			bullet_t dat;
			dat.ang = PI2 / 90 * i;
			dat.x = _boss->getX() + cos(dat.ang) * 50;
			dat.y = _boss->getY() + sin(dat.ang) * 50;
			dat.v = 0;
			dat.id = 0;
			dat.keepAlive = true;
			dat.type = eBulletType::eLaser;
			dat.color = i%eBulletColor::eColorNum;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}

	if (_counter >= 60) {
		int t = _counter - 60;
		if (t % 4 == 0) {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < 30; i++) {
					bullet_t dat;
					dat.ang = PI2 / 90 * i + PI2 / 360 * t + (j ? PI : 0);
					dat.x = _boss->getX() + cos(dat.ang) * 50;
					dat.y = _boss->getY() + sin(dat.ang) * 50;
					dat.v = 8;
					dat.id = 1;
					dat.isAddBlend = true;
					dat.type = eBulletType::eSparkSmall;
					dat.color = i%eBulletColor::eColorNum;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
				}
			}
		}
		if (t % 180 == 0) {
			_baseAngle[0] = Calculator::getIns()->getAngleFromBossToPlayer();
		}
		if (t % 180<40 && t % 5) {
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.ang = _baseAngle[0] + PI2 / 20 * i;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.v = 3;
				dat.id = 1;
				dat.isAddBlend = true;
				dat.type = eBulletType::eOdama;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
		if (t % 60 == 0) {
			_baseAngle[1] = Calculator::getIns()->getAngleFromBossToPlayer();
		}
		if (t % 60 < 15) {
			for (int i = 0; i < 45; i++) {
				bullet_t dat;
				dat.ang = _baseAngle[1] + PI2 / 45 * i;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.v = 12;
				dat.id = 2;
				dat.isAddBlend = true;
				dat.type = eBulletType::eKome;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			Utils::rotatePos(&b->dat.x, &b->dat.y, PI2 / 360, _boss->getX(), _boss->getY());
			b->dat.ang += PI2 / 360;
		}
		/*
		if (b->dat.id == 1) {
		if (b->dat.counter<120) {
		Utils::rotatePos(&b->dat.x, &b->dat.y, PI2 / 360, _boss->getX(), _boss->getY());
		b->dat.ang += PI2 / 360;
		}
		}
		*/
	}
}

void BarrageHard::Barrage047()
{
	const static int T = 40;
	if (_counter % 200 == 0) {
		_boss->moveBit(50);
	}
	for (int j = 0; j < 2; j++) {
		if ((T / 2)*j <= _counter % T && _counter % T <= (T / 2)*j + 16 && _counter % 1 == 0) {
			int t = _counter % (T / 2);
			if (t == 0) {
				_baseAngle[0] = randf2(PI);
			}
			for (int i = 0; i < 23; i++) {
				bullet_t dat;
				dat.x = _boss->getX();
				dat.y = _boss->getY();
				dat.ang = PI2 / 23 * i + _baseAngle[0] + PI / 250 * t*(j ? -1 : 1);
				dat.id = 0;
				dat.v = 7.5;
				dat.isAddBlend = true;
				dat.type = eBulletType::eKome;
				dat.color = j ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
}

/** スペル3 **/

void BarrageHard::Barrage048()
{
	if (_counter % 2 == 0) {
		for (int i = 0; i < 30; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = PI2 / 1200 * _counter + PI2 / 30 * i;
			dat.id = 0;
			dat.v = 8;
			dat.isAddBlend = true;
			dat.type = eBulletType::eKome;
			dat.color = eBulletColor::ePink;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
		}
	}
	if (_counter%70==69) {
		float angle = Calculator::getIns()->getAngleFromBossToPlayer();
		for (int i = 0; i < 20; i++) {
			bullet_t dat;
			dat.x = _boss->getX();
			dat.y = _boss->getY();
			dat.ang = angle + PI2 / 20 * i;
			dat.id = 3;
			dat.v = 3;
			dat.type = eBulletType::eTama;
			dat.color = eBulletColor::ePurple;
			_list.push_back(new Bullet(&dat));
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			float w = b->dat.x - Calculator::getIns()->getPlayerX();
			float h = b->dat.y - Calculator::getIns()->getPlayerY();
			static const float r = 120;
			if (w*w + h*h < r*r) {
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
				b->dat.v = 1 + randf2(0.3);
				b->dat.ang += randf2(PI / 360);
				b->dat.id = 1;
				b->dat.isAddBlend = false;
				b->dat.color = eBulletColor::eBlue;
				if (GetRand(3)) {
					b->dat.isAlive = false;
				}
			}
		}
	}
}

void BarrageHard::Barrage049()
{
	if (_counter % 200 == 0) {
		_boss->moveBit(50);
	}
	if (_counter == 0) {
		_baseAngle[0] = randf2(PI);
	}
	if (_counter % 8 == 0) {
		int t = _counter;
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 20; i++) {
				bullet_t dat;
				dat.x = _boss->getX() + cos(PI / 2 + PI / 90 * t*(j ? -1 : 1)) * 100;
				dat.y = _boss->getY() + sin(PI / 2 + PI / 90 * t*(j ? -1 : 1)) * 100;
				dat.ang = PI2 / 20 * i + _baseAngle[0] + PI / 300 * t;
				dat.id = 0;
				dat.v = 5;
				dat.type = eBulletType::eKome;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
}

/** スペル4 **/

void BarrageHard::Barrage050() {

	const static int N = 35;
	if (_counter % 120 == 119) {
		_boss->moveBit(50);
	}
	if (_boss->getResidualHp() >= 50) {
		if (_counter % 30 == 0) {
			float angle = randf2(PI);
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < N; i++) {
					for (int n = 0; n < 2; n++) {
						bullet_t dat;
						dat.ang = angle + PI2 / N * i;
						dat.x = _boss->getX();
						dat.y = _boss->getY();
						dat.v = 4;
						dat.id = j;
						dat.keepAlive = true;
						dat.type = eBulletType::eLaser;
						dat.color = eBulletColor::eBlue;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
				}
			}
		}
	}
	else {
		if (!_isDone) {
			for (auto b : _list) {
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
				b->dat.kill = true;
			}
			_isDone = true;
		}
		if (_counter % 19 == 0) {
			float angle = randf2(PI);
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < N; i++) {
					for (int n = 0; n < 2; n++) {
						bullet_t dat;
						dat.ang = angle + PI2 / N * i;
						dat.x = _boss->getX();
						dat.y = _boss->getY();
						dat.v = 4;
						dat.id = j;
						dat.keepAlive = true;
						dat.type = eBulletType::eLaser;
						dat.color = eBulletColor::ePink;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
				}
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter < 180) {
				b->dat.ang += PI / 150;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter < 180) {
				b->dat.ang -= PI / 150;
			}
		}
		if (b->dat.counter > 300) {
			b->dat.keepAlive = false;
		}
	}
}

/** スペル5 **/

void BarrageHard::Barrage051()
{
	if (_counter % 200 == 0) {
		_boss->moveBit(50);
	}
	if (_counter == 0) {
		_baseAngle[0] = randf2(PI);
	}
	if (_counter % 7 == 0) {
		int t = _counter;
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 22; i++) {
				bullet_t dat;
				dat.x = _boss->getX() + cos(PI / 2 + PI / 90 * t*(j ? -1 : 1)) * 100;
				dat.y = _boss->getY() + sin(PI / 2 + PI / 90 * t*(j ? -1 : 1)) * 100;
				dat.ang = PI2 / 22 * i + _baseAngle[0] + PI / 200 * t*(j ? -1 : 1);
				dat.id = 0;
				dat.v = 4.5 + (j ? 0 : 1.7);
				dat.type = eBulletType::eKome;
				dat.color = j ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
}

void BarrageHard::Barrage052()
{
	if (_boss->getResidualHp()>50) {
		if (_counter % 230 == 0) {
			float ang = randf2(PI);
			for (int i = 0; i < 9; i++) {
				bullet_t dat;
				dat.x = Calculator::getIns()->getPlayerX() + cos(PI2 / 9 * i + ang) * 150;
				dat.y = Calculator::getIns()->getPlayerY() + sin(PI2 / 9 * i + ang) * 150;
				dat.ang = PI2 / 9 * i + ang + PI;
				dat.id = _counter == 0 ? 0 : 1;
				dat.isAddBlend = true;
				dat.v = 0;
				dat.keepAlive = true;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
				_implBulletEffect->registBulletEffect(dat.x, dat.y, eBulletEffectType_Appear);
			}
			for (int j = 0; j < 7; j++) {
				float angle = randf2(PI);
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = Calculator::getIns()->getPlayerX() + cos(PI2 / 9 * i + angle) * 30 + cos(PI2 / 7 * j + ang) * 300;
					dat.y = Calculator::getIns()->getPlayerY() + sin(PI2 / 9 * i + angle) * 30 + sin(PI2 / 7 * j + ang) * 300;
					dat.ang = PI2 / 9 * i + angle + PI;
					dat.id = _counter == 0 ? 0 : 1;
					dat.isAddBlend = true;
					dat.v = 0;
					dat.keepAlive = true;
					dat.type = eBulletType::eBarrier;
					dat.color = eBulletColor::eBlue;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
					_implBulletEffect->registBulletEffect(dat.x, dat.y, eBulletEffectType_Appear);
				}
			}
		}
	}
	else {
		if (_isDone == false) {
			_isDone = true;
			for (auto b : _list) {
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y);
				b->dat.kill = true;
			}
		}
		if (_counter2 % 200 == 60) {
			float ang = randf2(PI);
			for (int i = 0; i < 9; i++) {
				bullet_t dat;
				dat.x = Calculator::getIns()->getPlayerX() + cos(PI2 / 9 * i + ang) * 150;
				dat.y = Calculator::getIns()->getPlayerY() + sin(PI2 / 9 * i + ang) * 150;
				dat.ang = PI2 / 9 * i + ang + PI;
				dat.id = _counter == 0 ? 0 : 1;
				dat.isAddBlend = true;
				dat.v = 0;
				dat.keepAlive = true;
				dat.type = eBulletType::eBarrier;
				dat.color = eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
				_implBulletEffect->registBulletEffect(dat.x, dat.y, eBulletEffectType_Appear);
			}
			for (int j = 0; j < 6; j++) {
				float angle = randf2(PI);
				for (int i = 0; i < 9; i++) {
					bullet_t dat;
					dat.x = Calculator::getIns()->getPlayerX() + cos(PI2 / 9 * i + angle) * 30 + cos(PI2 / 6 * j + ang) * 300;
					dat.y = Calculator::getIns()->getPlayerY() + sin(PI2 / 9 * i + angle) * 30 + sin(PI2 / 6 * j + ang) * 300;
					dat.ang = PI2 / 9 * i + angle + PI;
					dat.id = _counter == 0 ? 0 : 1;
					dat.isAddBlend = true;
					dat.v = 0;
					dat.keepAlive = true;
					dat.type = eBulletType::eBarrier;
					dat.color = eBulletColor::ePink;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
					_implBulletEffect->registBulletEffect(dat.x, dat.y, eBulletEffectType_Appear);
				}
			}
		}
		_counter2++;
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			if (b->dat.counter == 80) {
				b->dat.type = eBulletType::eOdama;
				b->dat.range = BULLET_RANGE[b->dat.type];
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y, eBulletEffectType_Appear);
			}
			if (80 <= b->dat.counter && b->dat.counter<180) {
				b->dat.v += 0.02;
			}
			if (b->dat.counter == 500) {
				b->dat.keepAlive = false;
			}
		}
		if (b->dat.id == 1) {
			if (b->dat.counter == 40) {
				b->dat.type = eBulletType::eOdama;
				b->dat.range = BULLET_RANGE[b->dat.type];
				_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y, eBulletEffectType_Appear);
			}
			if (60 <= b->dat.counter && b->dat.counter<160) {
				b->dat.v += 0.02;
			}
			if (b->dat.counter == 500) {
				b->dat.keepAlive = false;
			}
		}
	}
}

void BarrageHard::Barrage053()
{
	if (_counter % 2 == 0) {
		float angle = Calculator::getIns()->getAngleFromBossToPlayer();
		for (int j = 0; j < 2; j++) {
			for (int i = 6; i < 7; i++) {
				bullet_t dat;
				dat.x = _boss->getX() - cos(angle - PI / 2)*i * 24 * (j ? -1 : 1);
				dat.y = _boss->getY() - sin(angle - PI / 2)*i * 24 * (j ? -1 : 1);
				dat.ang = angle;
				dat.id = 0;
				dat.v = 8;
				dat.isAddBlend = true;
				dat.type = eBulletType::eOdama;
				dat.color = eBulletColor::eBlue;
				_list.push_back(new Bullet(&dat));
			}
		}
	}
	if (_counter % 200 == 0) {
		_boss->moveBit(50);
	}
	if (_counter == 0) {
		_baseAngle[0] = randf2(PI);
	}
	if (_counter % 8 == 0) {
		int t = _counter;
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 21; i++) {
				bullet_t dat;
				dat.x = _boss->getX() + cos(PI / 2 + PI / 90 * t*(j ? -1 : 1)) * 100;
				dat.y = _boss->getY() + sin(PI / 2 + PI / 90 * t*(j ? -1 : 1)) * 100;
				dat.ang = PI2 / 21 * i + _baseAngle[0] + PI / 200 * t*(j ? -1 : 1);
				dat.id = 0;
				dat.v = 5.2 + (j ? 0 : 1.5);
				dat.type = eBulletType::eKome;
				dat.color = j ? eBulletColor::eBlue : eBulletColor::ePink;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
			}
		}
	}
}

/** スペル6 **/
void BarrageHard::Barrage054()
{
	if (_counter == 0) {
		int TIME = (99 + 30) * 60;
		_boss->setTime(TIME);
		_boss->setSpellMAXTime(TIME);
	}

	if (_counter % 1 == 0 && _counter < 60) {
		bullet_t dat;
		dat.x = _boss->getX();
		dat.y = _boss->getY();
		dat.ang = Calculator::getIns()->getAngleFromBossToPlayer();
		dat.v = 0;
		dat.id = 0;
		dat.isAddBlend = true;
		dat.keepAlive = true;
		dat.color = eBulletColor::eBlue;
		dat.type = eBulletType::eKome;
		_list.push_back(new Bullet(&dat));
		if (_counter % 3 == 0) {
			SE::getIns()->setPlay(eSE_enemyShot);
		}
	}
	if (_counter % 1 == 0 && 700 <= _counter && _counter < 700 + 90) {
		bullet_t dat;
		dat.x = _boss->getX();
		dat.y = _boss->getY();
		dat.ang = Calculator::getIns()->getAngleFromBossToPlayer();
		dat.v = 0;
		dat.id = 1;
		dat.isAddBlend = true;
		dat.keepAlive = true;
		dat.color = eBulletColor::ePink;
		dat.type = eBulletType::eUmaibo;
		_list.push_back(new Bullet(&dat));
		if (_counter % 3 == 0) {
			SE::getIns()->setPlay(eSE_enemyShot);
		}
	}
	if (_counter % 1 == 0 && 1400 <= _counter && _counter < 1400 + 120) {
		bullet_t dat;
		dat.x = _boss->getX();
		dat.y = _boss->getY();
		dat.ang = Calculator::getIns()->getAngleFromBossToPlayer();
		dat.v = 0;
		dat.id = 2;
		dat.isAddBlend = true;
		dat.keepAlive = true;
		dat.color = eBulletColor::eYellow;
		dat.type = eBulletType::eSparkBig;
		_list.push_back(new Bullet(&dat));
		if (_counter % 3 == 0) {
			SE::getIns()->setPlay(eSE_enemyShot);
		}
	}


	if (_boss->getResidualHp()>55) {
		if (_counter % 240 == 0) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					int x = OUT_W / 3 / 2 + OUT_W / 3 * i;
					Laser* laser = new Laser();
					laser->color = eLaserColor_Blue;
					laser->angle = PI2 / 4 * j;
					laser->startpt.x = x;
					laser->startpt.y = -150;
					laser->counter = 0;
					laser->width = 15;
					laser->id = 0;
					laser->length = 150;
					laser->hitWidth = 0.85;
					_boss->registLaser(laser);
				}
			}
		}
		list<Laser*> *laserList = _boss->getLaserList();
		for (auto l : *laserList) {
			int cnt = l->counter;
			if (l->id == 0) {
				if (cnt<100) {
					l->startpt.y += 3;
				}
				else {
					l->startpt.y += 1;
				}
				l->angle += PI / 360;
			}
		}
	}
	else {
		{//レーザーを消す
			list<Laser*> *laserList = _boss->getLaserList();
			for (auto l : *laserList) {
				int cnt = l->counter;
				if (l->id == 0) {
					l->isAlive = false;
					_implBulletEffect->registBulletEffect(l->startpt.x, l->startpt.y);
				}
			}
		}


		int tm = 23;
		if (_boss->getResidualHp() < 5) {
			tm = 3;
		}
		else if (_boss->getResidualHp() < 20) {
			tm = 11;
		}
		else if (_boss->getResidualHp() < 30) {
			tm = 16;
		}
		if (_counter % tm == 0) {
			float angle = randf2(PI);
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 5; j++) {
					bullet_t dat;
					dat.x = _boss->getX();
					dat.y = _boss->getY();
					dat.ang = angle + PI2 / 6 * i;
					dat.v = 2 + j;
					dat.id = 10;
					dat.isAddBlend = true;
					dat.color = j;
					dat.type = eBulletType::eStar;
					_list.push_back(new Bullet(&dat));
				}
			}
			SE::getIns()->setPlay(eSE_enemyShot);
		}
	}
	{//発狂
		if (_boss->getReminingTime() < 15 * 60) {
			int tm = 3;
			if (_counter % tm == 0) {
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 5; j++) {
						bullet_t dat;
						dat.x = _boss->getX();
						dat.y = _boss->getY();
						dat.ang = PI2 / 417 * _counter + PI2 / 6 * i;
						dat.v = 2 + j;
						dat.id = 10;
						dat.isAddBlend = true;
						dat.color = j;
						dat.type = eBulletType::eStar;
						_list.push_back(new Bullet(&dat));
					}
				}
				SE::getIns()->setPlay(eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.id == 0) {
			int t = b->dat.counter % 100;
			if (t == 0) {
				b->dat.ang = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
			}
			if (0 <= t && t <  40) {
				b->dat.v += 0.1;
			}
			if (60 <= t && t < 100) {
				b->dat.v -= 0.1;
			}
		}
		if (b->dat.id == 1) {
			int t = b->dat.counter % 130;
			if (t == 0) {
				b->dat.ang = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
			}
			if (0 <= t && t <  60) {
				b->dat.v += 0.1;
			}
			if (70 <= t && t < 130) {
				b->dat.v -= 0.1;
			}
		}
		if (b->dat.id == 2) {
			int t = b->dat.counter % 160;
			if (t == 0) {
				b->dat.ang = Calculator::getIns()->getAngleToPlayer(b->dat.x, b->dat.y);
			}
			if (0 <= t && t <  60) {
				b->dat.v += 0.1;
			}
			if (100 <= t && t < 160) {
				b->dat.v -= 0.1;
			}
		}
	}

}

/** ラスト **/
//四聖龍陣弾幕結界
#define BARRAGE055_WAVENUM 7

#include "Keyboard.h"	//デバッグ用
#include "DebugMode.h"

static eBulletColor getBulletColor(int num)
{
	switch (num)
	{
	case 0:	return eBulletColor::eBlue;
	case 1: return eBulletColor::ePink;
	case 2: return eBulletColor::eGreen;
	case 3: return eBulletColor::ePurple;
	default:
		ERR("不正なnum(getBulletColor)");
		return eBulletColor::eColorNum;
	}
}

void BarrageHard::Barrage055()
{
	if (_counter == 0) {
		_boss->setPos(CENTER_X, CENTER_Y, 50);
		_angle = 0;
		int TIME = 9700-1250;
		_boss->setTime(TIME);
		_boss->setSpellMAXTime(TIME);
	}

	int WaveEachTime[BARRAGE055_WAVENUM] = { /*1250,*/1200,1120,1000,1320,1200,1400,1200 };
	int WaveTime[BARRAGE055_WAVENUM] = {};
	for (int i = 0; i < BARRAGE055_WAVENUM; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			WaveTime[i] += WaveEachTime[j];
		}
	}

	if (DebugMode::getIns()->isON)
	{
		//Lでウェーブスキップ
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_L) == 1)
		{
			for (int i = 0; i < BARRAGE055_WAVENUM; i++)
			{
				if (WaveTime[i] > _counter)
				{
					_counter = WaveTime[i];
					_list.clear();
					_launcher.clear();
					break;
				}
			}
		}
		//Kでウェーブバック
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_K) == 1)
		{
			for (int i = BARRAGE055_WAVENUM - 1; i >= 0; i--)
			{
				if (WaveTime[i] < _counter)
				{
					_counter = WaveTime[i - 1];
					_list.clear();
					_launcher.clear();
					break;
				}
			}
		}
	}
	/*
	if (_counter < WaveTime[0])
	{
		int count = _counter;	//このウェーブが始まってからの時間
		double deltaAngle = 0.03;	//1Fで回転する角度
		int range = 450;	//中心からの距離
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 500;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int accelTime = 600;	//弾が発射されてから加速するまでの時間
		int rollType = 1;	//回転方向

		if (count == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = range;
			if (count < preTime)
				r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			pl->x = _boss->getX() + cos(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			pl->y = _boss->getY() + sin(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			if (count >= preTime && count < shotTime)
			{
				if (pl->counter % 3 == 0) {
					bullet_t dat;
					dat.x = pl->x;
					dat.y = pl->y;
					dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
					dat.id = (shotTime - count) / 4;
					//					dat.id = (count -preTime ) / 4;
					dat.v = 3;
					dat.type = eBulletType::eBarrier;
					dat.keepAlive = true;
					dat.color = getBulletColor(pl->id);
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);

					dat.keepAlive = false;
					dat.id += 10;
					dat.v = 1.5;
					dat.ang += PI;
					//					_list.push_back(new Bullet(&dat));
					dat.ang += PI / 6;
					_list.push_back(new Bullet(&dat));
					dat.ang -= PI / 3;
					_list.push_back(new Bullet(&dat));

					dat.id = 300 + (shotTime - preTime - (count - preTime)) / 4;
					dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) + PI / 8 + PI / 3 * (double(count - preTime) / (endTime - shotTime));
					_list.push_back(new Bullet(&dat));
					dat.id = 300 + (count - preTime) / 4;
					dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) - PI / 8 - PI / 3 * (double(count - preTime) / (endTime - shotTime));
					_list.push_back(new Bullet(&dat));
				}
			}
		}
		for (auto b : _list)
		{
			if (b->dat.counter == b->dat.id + 1)
				b->dat.v = 0;
			if (b->dat.counter >= accelTime)
				b->dat.v = b->dat.v + 0.1;
		}
	}
	*/
	if (_counter < WaveTime[0])
	{
		int count = _counter;	//このウェーブが始まってからの時間
		double deltaAngle = 0.03;	//1Fで回転する角度
		int range = 450;	//中心からの距離
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 500;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int accelTime = 400;	//弾が発射されてから加速するまでの時間
								//		double ID1Spd = 2;	//お邪魔弾の初期速度
		int rollType = -1;	//回転方向

		if (count == 0)
		{
			_list.clear();
			for (int i = 0; i < 4; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = range;
			if (count < preTime)
				r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			pl->x = _boss->getX() + cos(deltaAngle * count*rollType*((pl->id % 2) * 2 - 1) - PI / 2 * pl->id) * r;
			pl->y = _boss->getY() + sin(deltaAngle * count*rollType*((pl->id % 2) * 2 - 1) - PI / 2 * pl->id) * r;
			if (count >= preTime && count < shotTime)
			{
				bullet_t dat;
				dat.x = pl->x;
				dat.y = pl->y;
				dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
				dat.type = eBulletType::eBarrier;
				dat.keepAlive = true;
				dat.color = getBulletColor(pl->id);
				if (pl->id % 2 == 0)	//ワインダー
				{
					if (pl->counter % 2 == 0)
					{
						dat.id = (shotTime - count) / 10 + 1;
						dat.v = 3;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
				}
				else	//お邪魔弾
				{
					if (pl->counter % 30 < 20 && pl->counter % 4 == 0)
					{
						dat.id = -((shotTime - count) / 3 + 20);
						dat.v = 3;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}

				}
				if (pl->counter % 2 == 0)
				{
					dat.keepAlive = false;
					dat.v = 1;
					dat.id = 0;
					dat.ang += PI + PI / 3;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
					dat.ang -= PI / 3 * 2;
					_list.push_back(new Bullet(&dat));
				}

			}
		}
		for (auto b : _list)
		{
			if (b->dat.id > 0)
			{
				if (b->dat.counter == b->dat.id + 1)
					b->dat.v = 0;
				if (b->dat.counter >= accelTime)
					b->dat.v = b->dat.v + 0.11;
			}
			if (b->dat.id < 0)
			{
				if (b->dat.counter == -b->dat.id + 1)
					b->dat.v = 0;
				if (_counter >= WaveTime[0] - 200)
					b->dat.v += 0.08;
				//				if (b->dat.counter == int(range/ID1Spd))
				//					b->dat.v = 0.8;
				//				if (b->dat.counter >= int(range / ID1Spd)+500 || _counter >WaveTime[1]-120)
				//					b->dat.v = b->dat.v + 0.1;
			}
		}
	}
	else if (_counter < WaveTime[1])
	{
		int count = _counter - WaveTime[0];	//このウェーブが始まってからの時間
		double deltaAngle = 0.03;	//1Fで回転する角度
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 500;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int accelTime = 600;	//弾が発射されてから加速するまでの時間
		int rollType = 1;	//回転方向

		if (count == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = 1;
			if (count < preTime)
				r = Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = 1 - 8 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			double x, y;
			double range = 400;
			Utils::getCycloid(x, y, range, range / 11 * 5, range / 11 * 3, PI2*1.25 / (shotTime - preTime)*(count - preTime) + pl->id*PI2*1.25);
			pl->x = x*r + CENTER_X;
			pl->y = y*r + CENTER_Y;

			if (count >= preTime && count < shotTime)
			{
				{
					if (pl->counter % 13 <= 2 && pl->counter % 1 == 0) {
						bullet_t dat;
						dat.x = pl->x;
						dat.y = pl->y;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						dat.ang += PI2 / 5;
						dat.id = (int)Utils::getLength(dat.x, dat.y, CENTER_X, CENTER_Y);
						dat.v = 0;
						dat.type = eBulletType::eBarrier;
						dat.keepAlive = true;
						dat.color = getBulletColor(pl->id);
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);

						dat.ang += PI2 / 5;
						_list.push_back(new Bullet(&dat));

						dat.ang += PI2 / 5;
						_list.push_back(new Bullet(&dat));
						dat.ang += PI2 / 5;
						_list.push_back(new Bullet(&dat));

						dat.id = 320;
						dat.ang += PI2 / 5;
						_list.push_back(new Bullet(&dat));
					}
				}
			}
		}
		for (auto b : _list)
		{
			if (b->dat.counter == b->dat.id + 1)
				b->dat.v = 0;
			if (count >= accelTime + b->dat.id)
				b->dat.v = b->dat.v + 0.05;
		}

		/*
		if (count == 0)
		{
		_list.clear();
		for (int i = 0; i < 4; i++)
		{
		_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[0]));
		_launcher[i]->id = i;
		}
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
		_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
		double r = range;
		if (count < preTime)
		r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
		if (count >= shotTime)
		r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

		if (pl->id % 2 == 0)	//ワインダー
		{
		pl->x = _boss->getX() + cos(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
		pl->y = _boss->getY() + sin(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
		}
		else	//サイクロイド状に動く
		{
		double deltaAngle2 = deltaAngle;
		double r2 = r*(0.5 + 0.3);
		if (count < preTime)
		r2 = r*0.5*double(count) / preTime;
		else if (count < shotTime)
		r2 = r*(0.5 + 0.2*double(count- preTime) / (shotTime-preTime));
		else
		r2 = r*0.7;
		double x = _boss->getX() + cos(deltaAngle2 * count*(-rollType) + PI*(pl->id/2)) *r2;
		double y = _boss->getY() + sin(deltaAngle2 * count*(-rollType) + PI*(pl->id / 2)) * r2;
		pl->x = x + cos(deltaAngle*0.7 * count*rollType + PI / 2 * pl->id) * r*0.15;
		pl->y = y + sin(deltaAngle*0.7 * count*rollType + PI / 2 * pl->id) * r*0.15;
		}
		if (count >= preTime && count < shotTime)
		{
		bullet_t dat;
		dat.x = pl->x;
		dat.y = pl->y;
		dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
		dat.type = eBulletType::eBarrier;
		dat.keepAlive = true;
		dat.color = getBulletColor(pl->id);
		if (pl->id % 2 == 0)	//ワインダー
		{
		if (pl->counter % 30 < 18 && pl->counter % 2 == 0)
		{
		dat.id = 0;
		dat.v = 0.1;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		}
		else	//お邪魔弾
		{
		if (pl->counter % 40 < 15 && pl->counter % 3 == 0)
		{
		dat.id = 1;
		dat.v = 1;
		_list.push_back(new Bullet(&dat));
		SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		}
		}
		}
		for (auto b : _list)
		{
		if (b->dat.id == 0)
		{
		if (b->dat.counter >= accelTime)
		b->dat.v = b->dat.v + 0.11;
		}
		if (b->dat.id == 1)
		{
		if (b->dat.counter == 20)
		b->dat.v = 0;
		if (b->dat.counter >= 320)
		b->dat.v = b->dat.v + 0.1;
		}
		}
		*/
	}
	/*
	else if (_counter < WaveTime[3])
	{
	int count = _counter - WaveTime[2];	//このウェーブが始まってからの時間
	double deltaAngle = 0.03;	//1Fで回転する角度
	int range = 400;	//中心からの距離
	int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
	int shotTime = 500;	//弾を撃ちおわる時間
	int endTime = 700;	//ランチャーが消える時間
	int accelTime = 400;	//弾が発射されてから加速するまでの時間
	int rollType = -1;	//回転方向

	if (count == 0)
	{
	_list.clear();
	for (int i = 0; i < 4; i++)
	{
	_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[0]));
	_launcher[i]->id = i;
	}
	SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	if (count == endTime)
	{
	_launcher.clear();
	}

	for (Launcher* pl : _launcher) {
	double r = range;
	if (count < preTime)
	r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
	if (count >= shotTime)
	r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

	//サイクロイド状に動く

	double deltaAngle2 = deltaAngle;
	double r2 = r*(0.5 + 0.3);
	if (count < preTime)
	r2 = r*0.5*double(count) / preTime;
	else if (count < shotTime)
	r2 = r*(0.5 + 0.4*double(count - preTime) / (shotTime-preTime));
	else
	r2 = r*0.9;
	double x = _boss->getX() + cos(deltaAngle2 * count+ PI*(pl->id / 2)) *r2;
	double y = _boss->getY() + sin(deltaAngle2 * count*(-rollType*((pl->id / 2) * 2 - 1)) + PI*(pl->id / 2)) * r2;
	pl->x = x + cos(deltaAngle*0.7 * count*rollType*((pl->id%2) * 2 - 1) + PI / 2 * pl->id) * r*0.15;
	pl->y = y + sin(deltaAngle*0.7 * count*rollType + PI / 2 * pl->id) * r*0.15;

	if (count >= preTime && count < shotTime)
	{
	bullet_t dat;
	dat.x = pl->x;
	dat.y = pl->y;
	dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
	dat.type = eBulletType::eBarrier;
	dat.keepAlive = true;
	dat.color = getBulletColor(pl->id);
	dat.id = 0;
	if (pl->id %2 == 0)
	{
	if (pl->counter % 30 > 18 && pl->counter % 3 == 0)
	{
	dat.v = 1;
	_list.push_back(new Bullet(&dat));
	SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	}
	else
	{
	if (pl->counter % 40 < 30 && pl->counter % 2 == 0)
	{
	dat.v = 1;
	_list.push_back(new Bullet(&dat));
	SE::getIns()->setPlay(eSE::eSE_enemyShot);
	}
	}
	}
	}
	for (auto b : _list)
	{
	//			if (b->dat.id == 0)
	{
	if (b->dat.counter == 20)
	b->dat.v = 0;
	if (b->dat.counter >= 350 && b->dat.counter < 360)
	b->dat.v = b->dat.v + 0.1;
	if (b->dat.counter >= 650)
	b->dat.v = b->dat.v + 0.1;
	}
	}
	}
	*/
	else if (_counter < WaveTime[2])
	{
		int count = _counter - WaveTime[1];	//このウェーブが始まってからの時間
		double deltaAngle = 0.02;	//1Fで回転する角度
		int range = 450;	//中心からの距離
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 500;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int rollType = 1;	//回転方向

		if (count == 0)
		{
			_list.clear();
			for (int i = 0; i < 4; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = range;
			if (count < preTime)
				r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			pl->x = _boss->getX() + cos(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			pl->y = _boss->getY() + sin(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			if (count >= preTime && count < shotTime)
			{
				if (pl->counter % 3 == 0 && pl->counter % 30 <16) {
					bullet_t dat;
					dat.x = pl->x;
					dat.y = pl->y;
					dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) + (count - preTime)*0.001;
					dat.id = (count - preTime) / 2;
					dat.v = 3;
					dat.type = eBulletType::eBarrier;
					dat.keepAlive = true;
					dat.color = getBulletColor(pl->id);
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);

					dat.keepAlive = false;

					dat.ang += PI / 6;
					_list.push_back(new Bullet(&dat));
					dat.ang -= PI / 3;
					_list.push_back(new Bullet(&dat));

				}
			}
		}
		for (auto b : _list)
		{
			//			if (b->dat.id == 0)
			{
				if (b->dat.counter == b->dat.id + 20)
					b->dat.v = 0;
				if (count >= endTime + 20 && count < endTime + 20 + 150)
					b->dat.v = b->dat.v + 0.05;
			}
		}
	}
	else if (_counter < WaveTime[3])
	{
		int count = _counter - WaveTime[2];	//このウェーブが始まってからの時間
		int range = 450;	//中心からの距離
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 435;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int rollType = -1;	//回転方向
		double deltaAngle = PI2 * 2 / (shotTime - preTime);	//1Fで回転する角度

															//shotTime - preTime = 315 = 3*5*7*3
		if (count == 0)
		{
			_list.clear();
			for (int i = 0; i < 4; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = range;
			if (count < preTime)
				r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			pl->x = _boss->getX() + cos(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			pl->y = _boss->getY() + sin(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			if (count >= preTime && count < shotTime)	//ピッタリ２週になるように調整
			{
				bullet_t dat;
				dat.x = pl->x;
				dat.y = pl->y;
				dat.v = 3;
				dat.type = eBulletType::eBarrier;
				dat.keepAlive = true;
				dat.color = getBulletColor(pl->id);
				switch (pl->id)
				{
				case 0:	//1波
					if ((count - preTime) % ((shotTime - preTime) / (5 * 9)) == 0)
					{
						//内側
						dat.id = 185;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						_list.push_back(new Bullet(&dat));
					}
					if ((count - preTime) % ((shotTime - preTime) / (3 * 7 * 5)) == 0)
					{
						//外側
						dat.id = 0;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						dat.ang += PI / 10;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
					}
					break;
				case 1:	//2波
					if ((count - preTime) % ((shotTime - preTime) / (7 * 5)) == 0)
					{
						//内側
						dat.id = 177;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						_list.push_back(new Bullet(&dat));
					}
					if ((count - preTime) % ((shotTime - preTime) / (7 * 9)) == 0)
					{
						//外側
						dat.id = 22;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						dat.ang -= PI / 13;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);

						//さらに外側
						dat.keepAlive = false;
						dat.ang += PI;
						dat.id = 10;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
					}
					break;
				case 2:	//3波
					if ((count - preTime) % ((shotTime - preTime) / (7 * 3)) == 0)
					{
						//内側
						dat.id = 169;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						_list.push_back(new Bullet(&dat));
					}
					if ((count - preTime) % ((shotTime - preTime) / (7 * 9)) == 0)
					{
						//外側
						dat.id = 44;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						dat.ang += PI / 17;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
						//さらに外側
						dat.keepAlive = false;
						dat.ang += PI;
						dat.id = 30;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
					}
					break;
				case 3:	//4波
					if ((count - preTime) % ((shotTime - preTime) / (7 * 3)) == 0)
					{
						//内側
						dat.id = 161;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						_list.push_back(new Bullet(&dat));
					}
					if ((count - preTime) % ((shotTime - preTime) / (9 * 7)) == 0)
					{
						//外側
						dat.id = 66;
						dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
						dat.ang -= PI / 70;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						SE::getIns()->setPlay(eSE::eSE_enemyShot);
						//さらに外側
						dat.keepAlive = false;
						dat.ang += PI;
						dat.id = 50;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
						dat.id += 7;
						_list.push_back(new Bullet(&dat));
					}
					break;
				default:
					ERR("弾幕結界にて異常なエラー");
					break;
				}
				/*
				for (int i = 0; i < 3; i++)
				{
				dat.ang += PI / 2 * i;
				dat.keepAlive = false;
				_list.push_back(new Bullet(&dat));
				}
				*/
			}
		}
		for (auto b : _list)
		{
			//			if (b->dat.id == 0)
			{
				if (b->dat.counter == b->dat.id)
					b->dat.v = 0;
				int t = 0;
				switch (b->dat.color)
				{
				case eBulletColor::eBlue: t = 0;  break;
				case eBulletColor::ePink: t = 140;  break;
				case eBulletColor::eGreen: t = 280;  break;
				case eBulletColor::ePurple: t = 420;  break;
				default:
					ERR("弾幕結界にて異常なエラー2");
					break;
				}
				if (count >= endTime + t)
				{
					b->dat.v += 0.04;
					if (b->dat.v >= 3)
						b->dat.v += 0.03;
				}
			}
		}
	}
	else if (_counter < WaveTime[4])
	{
		int count = _counter - WaveTime[3];	//このウェーブが始まってからの時間
		double deltaAngle = 0.03;	//1Fで回転する角度
		int range = 450;	//中心からの距離
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 500;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int rollType = 1;	//回転方向

		if (count == 0)
		{
			_list.clear();
			for (int i = 0; i < 4; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = range;
			if (count < preTime)
				r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			pl->x = _boss->getX() + cos(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			pl->y = _boss->getY() + sin(deltaAngle * count*rollType - PI / 2 * pl->id) * r;
			if (count >= preTime && count < shotTime)
			{
				if ((count - preTime) % 2 == 0 && (count - preTime) % 100 <90) {
					bullet_t dat;
					dat.x = pl->x;
					dat.y = pl->y;
					dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) + (count - preTime)*PI / 3 / (shotTime - preTime) - PI / 6;
					dat.id = (count - preTime) / 2;
					dat.v = 3;
					dat.type = eBulletType::eBarrier;
					dat.keepAlive = true;
					dat.color = getBulletColor(pl->id);
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);

					for (int i = 0; i < 3; i++)
					{
						dat.ang += PI / 2 * i;
						dat.keepAlive = false;
						_list.push_back(new Bullet(&dat));
					}
				}
			}
		}
		for (auto b : _list)
		{
			//			if (b->dat.id == 0)
			{
				if (b->dat.counter == (shotTime - preTime) / 2 - b->dat.id + 20)
					b->dat.v = 0;
				if (count >= endTime && count < endTime + 300)
					b->dat.v = b->dat.v + 0.01;
			}
		}
	}
	else if (_counter < WaveTime[5])
	{
		int count = _counter - WaveTime[4];	//このウェーブが始まってからの時間
		double deltaAngle = 0.02;	//1Fで回転する角度
		int range = 460;	//中心からの距離
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 520;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int rollType = 1;	//回転方向
		int deltatime = 270;	//１波と５波の感覚

		if (count == 0)
		{
			_list.clear();
			for (int i = 0; i < 8; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = range;
			if (count < preTime)
				r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			pl->x = _boss->getX() + cos(deltaAngle * count*rollType*((pl->id % 2) * 2 - 1) - PI / 4 * pl->id + PI / 8 + PI / 4 * (pl->id % 2 == 0)) * r;
			pl->y = _boss->getY() + sin(deltaAngle * count*rollType*((pl->id % 2) * 2 - 1) - PI / 4 * pl->id + PI / 8 + PI / 4 * (pl->id % 2 == 0)) * r;
			if (count >= preTime && count < shotTime)
			{
				if (count >= preTime && count < shotTime)
				{
					if (pl->id % 2 == 0)
					{
						if (pl->counter % 3 == 0) {	//ギリギリ当たる列
							bullet_t dat;
							dat.x = pl->x;
							dat.y = pl->y;
							dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) - (count - preTime)*0.001;
							dat.id = (count - preTime) / 2;
							if ((pl->id % 4) == 0) dat.id += 10000;
							dat.v = 3;
							dat.type = eBulletType::eBarrier;
							dat.keepAlive = true;
							//					dat.color = getBulletColor(pl->id);
							dat.color = eBulletColor::eBlue;
							_list.push_back(new Bullet(&dat));
							SE::getIns()->setPlay(eSE::eSE_enemyShot);
						}
					}
					else
					{
						if (pl->counter % 3 == 0) {	//ギリギリ当たる列(2wave
							bullet_t dat;
							dat.x = pl->x;
							dat.y = pl->y;
							dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) + (count - preTime)*0.001;
							dat.id = (count - preTime) / 2;
							if ((pl->id % 4) == 1) dat.id += 10000;
							dat.v = 3;
							dat.type = eBulletType::eBarrier;
							dat.keepAlive = true;
							//					dat.color = getBulletColor(pl->id);
							dat.color = eBulletColor::ePink;
							_list.push_back(new Bullet(&dat));
							SE::getIns()->setPlay(eSE::eSE_enemyShot);
						}
					}
					if (pl->id % 2 == 1)
					{
						if (pl->counter % 30 < 12 && pl->counter % 3 == 0) {	//ギリギリ当たらない列
							bullet_t dat;
							dat.x = pl->x;
							dat.y = pl->y;
							dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) - PI / 3 * 0.04 - PI / 3 * 0.96*double(count - preTime) / (shotTime - preTime);
							dat.id = (count - preTime) / 2;
							dat.v = 2;
							dat.type = eBulletType::eBarrier;
							dat.keepAlive = true;
							dat.color = eBulletColor::eGreen;
							_list.push_back(new Bullet(&dat));
							SE::getIns()->setPlay(eSE::eSE_enemyShot);

							dat.id += 10000;
							dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) + PI / 3 * 0.04 + PI / 3 * 0.96*double(count - preTime) / (shotTime - preTime);
							_list.push_back(new Bullet(&dat));

						}
					}
					else
					{
						if (pl->counter % 30 < 27 && pl->counter % 30 >= 15 && pl->counter % 3 == 0) {	//ギリギリ当たらない列(2wave
							bullet_t dat;
							dat.x = pl->x;
							dat.y = pl->y;
							dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) + PI / 3 * 0.04 + PI / 3 * 0.96*double(count - preTime) / (shotTime - preTime);
							dat.id = (count - preTime) / 2;
							dat.v = 2;
							dat.type = eBulletType::eBarrier;
							dat.keepAlive = true;
							dat.color = eBulletColor::ePurple;
							_list.push_back(new Bullet(&dat));
							SE::getIns()->setPlay(eSE::eSE_enemyShot);

							dat.id += 10000;
							dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y) - PI / 3 * 0.04 - PI / 3 * 0.96*double(count - preTime) / (shotTime - preTime);
							_list.push_back(new Bullet(&dat));
						}
					}
				}
			}
		}
		for (auto b : _list)
		{
			if (b->dat.keepAlive = true)
			{
				int adjustT = 60;
				if (b->dat.counter == (b->dat.id % 10000) + 1)
					b->dat.v = 0;
				switch (b->dat.color)
				{
				case eBulletColor::eBlue:
					if (b->dat.id >= (b->dat.id >= 10000) * 10000)
					{
						if (count >= endTime + 10 + adjustT + deltatime*(b->dat.id >= 10000))
							b->dat.v = b->dat.v + 0.07;
					}
					break;
				case eBulletColor::eGreen:
					if (b->dat.id >= (b->dat.id >= 10000) * 10000)
					{
						if (count >= endTime - (b->dat.id % 10000) + 80 + adjustT + deltatime*(b->dat.id >= 10000))
							b->dat.v += 0.07;
					}
					break;
				case eBulletColor::ePink:
					if (b->dat.id >= (b->dat.id >= 10000) * 10000)
					{
						if (count >= endTime + 140 + adjustT + deltatime*(b->dat.id >= 10000))
							b->dat.v = b->dat.v + 0.07;
					}
					break;
				case eBulletColor::ePurple:
					if (b->dat.id >= (b->dat.id >= 10000) * 10000)
					{
						if (count >= endTime - (b->dat.id % 10000) + 210 + adjustT + deltatime*(b->dat.id >= 10000))
							b->dat.v += 0.07;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	else if (_counter < WaveTime[6])
	{
		int count = _counter - WaveTime[5];	//このウェーブが始まってからの時間
		double deltaAngle = 0.05;	//1Fで回転する角度
									//		double deltaAngle = 0.070;	//1Fで回転する角度
		int range = 460;	//中心からの距離
		int preTime = 120;	//ランチャーが発射されてから弾を打つまでの時間
		int shotTime = 500;	//弾を撃ちおわる時間
		int endTime = 700;	//ランチャーが消える時間
		int rollType = -1;	//回転方向

		if (count == 0)
		{
			_list.clear();
			for (int i = 0; i < 4; i++)
			{
				_launcher.push_back(new Launcher(_boss->getX(), _boss->getY(), _launcherImage[((i + 1) % 4)]));
				_launcher[i]->id = i;
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShot);
		}
		if (count == endTime)
		{
			_launcher.clear();
		}

		for (Launcher* pl : _launcher) {
			double r = range;
			if (count < preTime)
				r = range*Utils::GetBeje(1, Utils::EBejeType_QuickSlow, double(count) / preTime);
			if (count >= shotTime)
				r = range - range * 4 * Utils::GetBeje(1, Utils::EBejeType_SlowQuick, double(count - shotTime) / (endTime - shotTime));

			pl->x = _boss->getX() + cos(deltaAngle * count*rollType - PI / 2 * pl->id - PI / 20) * r;
			pl->y = _boss->getY() + sin(deltaAngle * count*rollType - PI / 2 * pl->id - PI / 20) * r;
			if (count >= preTime && count < shotTime)
			{
				bullet_t dat;
				dat.x = pl->x;
				dat.y = pl->y;
				dat.ang = Utils::getAngle(dat.x, dat.y, CENTER_X, CENTER_Y);
				dat.id = (count - preTime) / 4;
				dat.v = 3.7;
				dat.type = eBulletType::eBarrier;
				dat.keepAlive = true;
				dat.color = getBulletColor(pl->id);
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);

				dat.v = 5;
				dat.ang += PI;
				dat.keepAlive = false;
				_list.push_back(new Bullet(&dat));

				dat.ang += PI / 6;
				_list.push_back(new Bullet(&dat));
				dat.ang += PI / 6 * 2;
				_list.push_back(new Bullet(&dat));
			}
		}
		for (auto b : _list)
		{
			if (b->dat.keepAlive == true)
			{
				if (b->dat.counter == b->dat.id + 1)
					b->dat.v = 0;
				if (count == endTime + 20)
					b->dat.v = b->dat.v + 0.85;
				if (count > endTime + 20 + 10)
					b->dat.v = b->dat.v *0.99;
			}
		}
	}

}

void BarrageHard::Barrage056() {}
void BarrageHard::Barrage057() {}
void BarrageHard::Barrage058() {}
void BarrageHard::Barrage059() {}
void BarrageHard::Barrage060() {}
void BarrageHard::Barrage061() {}
void BarrageHard::Barrage062() {}
void BarrageHard::Barrage063() {}
void BarrageHard::Barrage064() {}
void BarrageHard::Barrage065() {}
void BarrageHard::Barrage066() {}
void BarrageHard::Barrage067() {}
void BarrageHard::Barrage068() {}
void BarrageHard::Barrage069() {}
void BarrageHard::Barrage070() {}
void BarrageHard::Barrage071() {}
void BarrageHard::Barrage072() {}
void BarrageHard::Barrage073() {}
void BarrageHard::Barrage074() {}
void BarrageHard::Barrage075() {}
void BarrageHard::Barrage076() {}
void BarrageHard::Barrage077() {}
void BarrageHard::Barrage078() {}
void BarrageHard::Barrage079() {}
void BarrageHard::Barrage080() {}
void BarrageHard::Barrage081() {}
void BarrageHard::Barrage082() {}
void BarrageHard::Barrage083() {}
void BarrageHard::Barrage084() {}
void BarrageHard::Barrage085() {}
void BarrageHard::Barrage086() {}
void BarrageHard::Barrage087() {}
void BarrageHard::Barrage088() {}
void BarrageHard::Barrage089() {}
void BarrageHard::Barrage090() {}
void BarrageHard::Barrage091() {}
void BarrageHard::Barrage092() {}
void BarrageHard::Barrage093() {}
void BarrageHard::Barrage094() {}
void BarrageHard::Barrage095() {}
void BarrageHard::Barrage096() {}
void BarrageHard::Barrage097() {}
void BarrageHard::Barrage098() {}
void BarrageHard::Barrage099() {}
