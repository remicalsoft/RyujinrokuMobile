#include "Define.h"
#include <math.h>
#include "BarrageZakoHard.h"
#include "Calculator.h"
#include <DxLib.h>
#include "SE.h"
#include "Utils.h"

using namespace std;

void BarrageZakoHard::Barrage000() {
	//nothing
}

void BarrageZakoHard::Barrage001() {
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
				dat.v = 8+i*1.3;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 30) {
			b->dat.v -= 0.2f;
		}
	}
}

void BarrageZakoHard::Barrage002() {
	if (_enemy->_isAlive) {
		if (_counter % 60 == 0) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y);
				dat.v = 8 + i*1.3;;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
		}
	}
	for (auto b : _list) {
		if (b->dat.counter < 30) {
			b->dat.v -= 0.2f;
		}
	}
}

void BarrageZakoHard::Barrage003() {
	if (_enemy->_isAlive) {
		if (_counter % 100 == 0 || _counter % 100 == 10 || _counter % 100 == 20 || _counter % 100 == 30 || _counter % 100 == 40) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = angle - PI / 30 * 2 + PI / 30 * j - PI / 2*2 + PI / 2 * i;
					dat.v = 10;
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

void BarrageZakoHard::Barrage004() {
	if (_enemy->_isAlive) {
		if (_counter % 80 == 0 && _counter <= 80 * 3) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 13; i++) {
				for (int j = i; j < 13; j++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = (_counter / 100) % 2 ? angle - PI / 50 * 6 + PI / 50 * i : angle + PI / 50 * 6 - PI / 50 * i;
					dat.v = (_counter / 100) % 2 ? 3.4 + 0.2*j : 3.4 + 0.2 * 11 - 0.2*j;
					dat.type = _script.bulletType;
					dat.color = _script.bulletColor;
					_list.push_back(new Bullet(&dat));
					SE::getIns()->setPlay(eSE::eSE_enemyShot);
				}
			}
		}
	}
}

void BarrageZakoHard::Barrage005() {
	if (_enemy->_isAlive) {
		if (_counter % 60 == 0 || _counter % 60 == 8 || _counter % 60 == 16) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x-40+40*i;
				dat.y = _enemy->_y;
				dat.ang = PI / 2;
				dat.v = 8;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
				SE::getIns()->setPlay(eSE::eSE_enemyShot);
			}
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x,dat.y);
			dat.v = 9;
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

void BarrageZakoHard::Barrage006()
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
		if (60 < b->dat.counter && b->dat.counter <= 60 + 70) {
			b->dat.v += 0.1f;
		}
	}
}
void BarrageZakoHard::Barrage007()
{
	if (_enemy->_isAlive) {
		if (_counter < 60) {
			for (int i = 0; i < 2; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 60 * _counter;
				dat.v = 5+i*2;
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
			b->dat.v += 0.1f+0.04*b->dat.id;
		}
	}
}
void BarrageZakoHard::Barrage008()
{
	if (_enemy->_isAlive) {
		if (_counter % 3 == 0 && _counter < 240) {
			bullet_t dat;
			dat.x = _enemy->_x;
			dat.y = _enemy->_y;
			dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) + randf2(PI / 3);
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

void BarrageZakoHard::Barrage009()
{
	if (_enemy->_isAlive) {
		if (_counter % 2 == 0 && _counter < 180) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI / 2 - PI2 / 120 * _enemy->_counter + PI2 / 4 * i + randf2(PI / 360);
				dat.v = 11;
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

void BarrageZakoHard::Barrage010()
{
	if (_enemy->_isAlive) {
		if (_counter % 35 == 0 && _counter < 200) {
			float angle = randf2(PI);
			for (int i = 0; i < 30; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 30 * i + angle;
				dat.v = 9;
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
void BarrageZakoHard::Barrage011()
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 4; i++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = angle - PI / 20 + PI / 20 * j;
					dat.v = 6 + 2 * i;
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
void BarrageZakoHard::Barrage012()
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
				for (int j = 0; j < 2; j++) {
					for (int i = 0; i < 15; i++) {
						bullet_t dat;
						dat.x = b->dat.x;
						dat.y = b->dat.y;
						dat.ang = angle - PI / 4 + PI * 0.6 / 15 * i;
						dat.v = 1 + 0.1*i + j;
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
}
void BarrageZakoHard::Barrage013()
{
	if (_enemy->_isAlive) {
		if (_counter % 3 == 0) {
			float angle = Calculator::getIns()->getAngleToPlayer(_enemy->_x, _enemy->_y);
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = angle + randf2(PI / 20) + PI2 / 3 * i;
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
void BarrageZakoHard::Barrage014()
{
	if (_enemy->_isAlive) {
		if (_counter % 4 == 0 && _counter<40) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x-5+5*i;
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
}
void BarrageZakoHard::Barrage015()
{
	if (_enemy->_isAlive) {
		if (_counter % 25 == 0 && _counter<50) {
			for (int i = 0; i < 3; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y)-PI/140+PI/140*i;
				dat.v = 10;
				dat.id = 0;
				dat.type = _script.bulletType;
				dat.color = _script.bulletColor;
				_list.push_back(new Bullet(&dat));
			}
			SE::getIns()->setPlay(eSE::eSE_enemyShotSmall);
		}
	}
}

void BarrageZakoHard::Barrage016()
{
	if (_enemy->_isAlive) {
		if (_counter < 60) {
			for (int i = 0; i < 5; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 2 + PI2 / 80 * _counter;
				dat.v = 7 + i;
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

void BarrageZakoHard::Barrage017()
{
	if (_enemy->_isAlive) {
		if (_counter<40 && _counter % 2 == 0) {
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

void BarrageZakoHard::Barrage018()
{
	if (_enemy->_isAlive) {
		if (_counter<120 && _counter % 2 == 0) {
			for (int i = 0; i < 6; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = PI2 / 120 * _counter + PI2 / 6 * i;
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

void BarrageZakoHard::Barrage019()
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			for (int i = 0; i < 6; i++) {
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
void BarrageZakoHard::Barrage020()
{
	if (_enemy->_isAlive) {
		if (_counter < 90 && _counter % 20 == 0) {
			for (int j = 0; j < 10; j++) {
				for (int i = 0; i < 5; i++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI2 / 60 + PI2 / 120 * i + PI2/10*j;
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

void BarrageZakoHard::Barrage021()
{
	if (_enemy->_isAlive) {
		if (_counter == 0) {
			for (int j = 0; j < 10; j++) {
				for (int i = 0; i < 3; i++) {
					bullet_t dat;
					dat.x = _enemy->_x;
					dat.y = _enemy->_y;
					dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 50 + PI / 50 * i + PI2/10*j;
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
}

void BarrageZakoHard::Barrage022()
{
	if (_enemy->_isAlive) {
		if (_counter < 60) {
			for (int i = 0; i < 4; i++) {
				bullet_t dat;
				dat.x = _enemy->_x;
				dat.y = _enemy->_y;
				dat.ang = Calculator::getIns()->getAngleToPlayer(dat.x, dat.y) - PI / 2 + PI2 / 80 * _counter;
				dat.v = 6 + 0.5*i;
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

void BarrageZakoHard::Barrage023()
{
}

void BarrageZakoHard::Barrage024()
{
}

void BarrageZakoHard::Barrage025()
{
}

void BarrageZakoHard::Barrage026()
{
}

void BarrageZakoHard::Barrage027()
{
}

void BarrageZakoHard::Barrage028()
{
}

void BarrageZakoHard::Barrage029()
{
}

void BarrageZakoHard::Barrage030()
{
	if (_enemy->_isAlive) {
		if (_counter % 20 == 10 && _counter < 240) {
			for (int i = 0; i < 5; i++) {
				bullet_t dat;
				dat.x = _enemy->getX();
				dat.y = _enemy->getY();
				dat.ang = Calculator::getIns()->getAngleToPlayer(_enemy->getX(), _enemy->getY()) - PI / 4 + PI / 8 * i;
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

void BarrageZakoHard::Barrage031()
{
}

void BarrageZakoHard::Barrage032()
{
}

void BarrageZakoHard::Barrage033()
{
}

void BarrageZakoHard::Barrage034()
{
}

void BarrageZakoHard::Barrage035()
{
}

void BarrageZakoHard::Barrage036()
{
}

void BarrageZakoHard::Barrage037()
{
}

void BarrageZakoHard::Barrage038()
{
}

void BarrageZakoHard::Barrage039()
{
}

void BarrageZakoHard::Barrage040()
{
}

void BarrageZakoHard::Barrage041()
{
}

void BarrageZakoHard::Barrage042()
{
}

void BarrageZakoHard::Barrage043()
{
}

void BarrageZakoHard::Barrage044()
{
}

void BarrageZakoHard::Barrage045()
{
}

void BarrageZakoHard::Barrage046()
{
}

void BarrageZakoHard::Barrage047()
{
}

void BarrageZakoHard::Barrage048()
{
}

void BarrageZakoHard::Barrage049()
{
}

void BarrageZakoHard::Barrage050()
{
}
void BarrageZakoHard::Barrage051() {}
void BarrageZakoHard::Barrage052() {}
void BarrageZakoHard::Barrage053() {}
void BarrageZakoHard::Barrage054() {}
void BarrageZakoHard::Barrage055() {}
void BarrageZakoHard::Barrage056() {}
void BarrageZakoHard::Barrage057() {}
void BarrageZakoHard::Barrage058() {}
void BarrageZakoHard::Barrage059() {}
void BarrageZakoHard::Barrage060() {}
void BarrageZakoHard::Barrage061() {}
void BarrageZakoHard::Barrage062() {}
void BarrageZakoHard::Barrage063() {}
void BarrageZakoHard::Barrage064() {}
void BarrageZakoHard::Barrage065() {}
void BarrageZakoHard::Barrage066() {}
void BarrageZakoHard::Barrage067() {}
void BarrageZakoHard::Barrage068() {}
void BarrageZakoHard::Barrage069() {}
void BarrageZakoHard::Barrage070() {}
void BarrageZakoHard::Barrage071() {}
void BarrageZakoHard::Barrage072() {}
void BarrageZakoHard::Barrage073() {}
void BarrageZakoHard::Barrage074() {}
void BarrageZakoHard::Barrage075() {}
void BarrageZakoHard::Barrage076() {}
void BarrageZakoHard::Barrage077() {}
void BarrageZakoHard::Barrage078() {}
void BarrageZakoHard::Barrage079() {}
void BarrageZakoHard::Barrage080() {}
void BarrageZakoHard::Barrage081() {}
void BarrageZakoHard::Barrage082() {}
void BarrageZakoHard::Barrage083() {}
void BarrageZakoHard::Barrage084() {}
void BarrageZakoHard::Barrage085() {}
void BarrageZakoHard::Barrage086() {}
void BarrageZakoHard::Barrage087() {}
void BarrageZakoHard::Barrage088() {}
void BarrageZakoHard::Barrage089() {}
void BarrageZakoHard::Barrage090() {}
void BarrageZakoHard::Barrage091() {}
void BarrageZakoHard::Barrage092() {}
void BarrageZakoHard::Barrage093() {}
void BarrageZakoHard::Barrage094() {}
void BarrageZakoHard::Barrage095() {}
void BarrageZakoHard::Barrage096() {}
void BarrageZakoHard::Barrage097() {}
void BarrageZakoHard::Barrage098() {}
void BarrageZakoHard::Barrage099() {}
BarrageZakoHard::BarrageZakoHard(std::shared_ptr<Enemy> enemy, Script script, IPlayerInfoGettable* impl, BulletEffectRegistable* implBulletDisappearEffectRegistable) : BarrageZako(enemy, script, impl, implBulletDisappearEffectRegistable)
{
}

BarrageZakoHard::~BarrageZakoHard()
{
}
