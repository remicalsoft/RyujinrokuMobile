#include "Barrage.h"
#include "Bullet.h"
//#include "BulletKilledEffectMgr.h"
//#include "SE.h"
//#include "Utils.h"

using namespace std;

//Barrage::Barrage(IPlayerInfoGettable* impl, BulletEffectRegistable *implBulletDisappearEffectRegistable)
Barrage::Barrage(std::shared_ptr<Context> context):Drawable(context)
{
	setFunc();
	//_implPlayerInfoGettable = impl;
	//_implBulletEffect = implBulletDisappearEffectRegistable;
}


Barrage::~Barrage()
{
	//for (auto b :a _list) {
	//	BulletKilledEffectMgr::getIns()->regist(b->dat.x, b->dat.y, (eBulletColor)b->dat.color);
	//}
}

void Barrage::updateCollision()
{
//	for (list<Bullet*>::iterator it = _list.begin(); it != _list.end();) {
//		if ((*it)->dat.hit == false) {
//			it++;
//			continue;
//		}
//		float x = (*it)->dat.x;
//		float y = (*it)->dat.y;
//		float v = (*it)->dat.v;
//		float angle = (*it)->dat.ang;
//		float range = (*it)->dat.range;
////		bool isHit = false;
//		float px = _implPlayerInfoGettable->getX();
//		float py = _implPlayerInfoGettable->getY();
//		float pRange = _implPlayerInfoGettable->getHitRange();
//		if (Utils::isHit(x, y, v, angle, range, px, py, pRange)) {
//			if (_implPlayerInfoGettable->isInvincible()) {
//			}
//			else {
//				_implPlayerInfoGettable->die();
//			}
//			if (!(*it)->dat.keepAlive) {
//				it = _list.erase(it);
//			}
//			else {
//				it++;
//			}
//		}
//		else {
//			it++;
//		}
//	}
}

void Barrage::updateGraze()
{
	//for (auto b : _list)
	//{
	//	if (b->dat.hit == false || b->dat.graze == false) {
	//		continue;
	//	}
	//	float x = b->dat.x;
	//	float y = b->dat.y;
	//	float v = b->dat.v;
	//	float angle = b->dat.ang;
	//	float range = b->dat.range;
	//	float px = _implPlayerInfoGettable->getX();
	//	float py = _implPlayerInfoGettable->getY();
	//	float pRange = _implPlayerInfoGettable->getGrazeRange();
	//	if (Utils::isHit(x, y, v, angle, range, px, py, pRange)) {
	//		GameData::getIns()->grazeIncrement();
	//		b->dat.graze = false;
	//		_implPlayerInfoGettable->registerGraze();
	//	}
	//}
}

bool comp(Bullet* v1, Bullet* v2) {
	//if (BULLET_SORT[v1->dat.type] > BULLET_SORT[v2->dat.type]) {
	//	return true;
	//}
	//else {
	//	return false;
	//}
	return true;
}

bool Barrage::update()
{
	//updateGraze();
	//updateCollision();
	//for (auto b : _list) {
	//	if (!b->dat.keepAlive && _implPlayerInfoGettable->isBombing()) {
	//		float px = _implPlayerInfoGettable->getX();
	//		float py = _implPlayerInfoGettable->getY();
	//		float pr = _implPlayerInfoGettable->getBombR();
	//		if (px - pr <= b->dat.x && b->dat.x <= px + pr && b->dat.y <= py) {
	//			b->dat.isAlive = false;
	//			_implBulletEffect->registBulletEffect(b->dat.x, b->dat.y, eBulletEffectType_Disappear);
	//			GameData::getIns()->plusScore(1.0, GameData::eScoreEraseBullet);
	//		}
	//	}
	//}
	//_list.sort(comp);
	return true;
}

void Barrage::setFunc() {
	_funcList.push_back(&Barrage::Barrage000);
	_funcList.push_back(&Barrage::Barrage001);
	_funcList.push_back(&Barrage::Barrage002);
	_funcList.push_back(&Barrage::Barrage003);
	_funcList.push_back(&Barrage::Barrage004);
	_funcList.push_back(&Barrage::Barrage005);
	_funcList.push_back(&Barrage::Barrage006);
	_funcList.push_back(&Barrage::Barrage007);
	_funcList.push_back(&Barrage::Barrage008);
	_funcList.push_back(&Barrage::Barrage009);
	_funcList.push_back(&Barrage::Barrage010);
	_funcList.push_back(&Barrage::Barrage011);
	_funcList.push_back(&Barrage::Barrage012);
	_funcList.push_back(&Barrage::Barrage013);
	_funcList.push_back(&Barrage::Barrage014);
	_funcList.push_back(&Barrage::Barrage015);
	_funcList.push_back(&Barrage::Barrage016);
	_funcList.push_back(&Barrage::Barrage017);
	_funcList.push_back(&Barrage::Barrage018);
	_funcList.push_back(&Barrage::Barrage019);
	_funcList.push_back(&Barrage::Barrage020);
	_funcList.push_back(&Barrage::Barrage021);
	_funcList.push_back(&Barrage::Barrage022);
	_funcList.push_back(&Barrage::Barrage023);
	_funcList.push_back(&Barrage::Barrage024);
	_funcList.push_back(&Barrage::Barrage025);
	_funcList.push_back(&Barrage::Barrage026);
	_funcList.push_back(&Barrage::Barrage027);
	_funcList.push_back(&Barrage::Barrage028);
	_funcList.push_back(&Barrage::Barrage029);
	_funcList.push_back(&Barrage::Barrage030);
	_funcList.push_back(&Barrage::Barrage031);
	_funcList.push_back(&Barrage::Barrage032);
	_funcList.push_back(&Barrage::Barrage033);
	_funcList.push_back(&Barrage::Barrage034);
	_funcList.push_back(&Barrage::Barrage035);
	_funcList.push_back(&Barrage::Barrage036);
	_funcList.push_back(&Barrage::Barrage037);
	_funcList.push_back(&Barrage::Barrage038);
	_funcList.push_back(&Barrage::Barrage039);
	_funcList.push_back(&Barrage::Barrage040);
	_funcList.push_back(&Barrage::Barrage041);
	_funcList.push_back(&Barrage::Barrage042);
	_funcList.push_back(&Barrage::Barrage043);
	_funcList.push_back(&Barrage::Barrage044);
	_funcList.push_back(&Barrage::Barrage045);
	_funcList.push_back(&Barrage::Barrage046);
	_funcList.push_back(&Barrage::Barrage047);
	_funcList.push_back(&Barrage::Barrage048);
	_funcList.push_back(&Barrage::Barrage049);
	_funcList.push_back(&Barrage::Barrage050);
	_funcList.push_back(&Barrage::Barrage051);
	_funcList.push_back(&Barrage::Barrage052);
	_funcList.push_back(&Barrage::Barrage053);
	_funcList.push_back(&Barrage::Barrage054);
	_funcList.push_back(&Barrage::Barrage055);
	_funcList.push_back(&Barrage::Barrage056);
	_funcList.push_back(&Barrage::Barrage057);
	_funcList.push_back(&Barrage::Barrage058);
	_funcList.push_back(&Barrage::Barrage059);
	_funcList.push_back(&Barrage::Barrage060);
	_funcList.push_back(&Barrage::Barrage061);
	_funcList.push_back(&Barrage::Barrage062);
	_funcList.push_back(&Barrage::Barrage063);
	_funcList.push_back(&Barrage::Barrage064);
	_funcList.push_back(&Barrage::Barrage065);
	_funcList.push_back(&Barrage::Barrage066);
	_funcList.push_back(&Barrage::Barrage067);
	_funcList.push_back(&Barrage::Barrage068);
	_funcList.push_back(&Barrage::Barrage069);
	_funcList.push_back(&Barrage::Barrage070);
	_funcList.push_back(&Barrage::Barrage071);
	_funcList.push_back(&Barrage::Barrage072);
	_funcList.push_back(&Barrage::Barrage073);
	_funcList.push_back(&Barrage::Barrage074);
	_funcList.push_back(&Barrage::Barrage075);
	_funcList.push_back(&Barrage::Barrage076);
	_funcList.push_back(&Barrage::Barrage077);
	_funcList.push_back(&Barrage::Barrage078);
	_funcList.push_back(&Barrage::Barrage079);
	_funcList.push_back(&Barrage::Barrage080);
	_funcList.push_back(&Barrage::Barrage081);
	_funcList.push_back(&Barrage::Barrage082);
	_funcList.push_back(&Barrage::Barrage083);
	_funcList.push_back(&Barrage::Barrage084);
	_funcList.push_back(&Barrage::Barrage085);
	_funcList.push_back(&Barrage::Barrage086);
	_funcList.push_back(&Barrage::Barrage087);
	_funcList.push_back(&Barrage::Barrage088);
	_funcList.push_back(&Barrage::Barrage089);
	_funcList.push_back(&Barrage::Barrage090);
	_funcList.push_back(&Barrage::Barrage091);
	_funcList.push_back(&Barrage::Barrage092);
	_funcList.push_back(&Barrage::Barrage093);
	_funcList.push_back(&Barrage::Barrage094);
	_funcList.push_back(&Barrage::Barrage095);
	_funcList.push_back(&Barrage::Barrage096);
	_funcList.push_back(&Barrage::Barrage097);
	_funcList.push_back(&Barrage::Barrage098);
	_funcList.push_back(&Barrage::Barrage099);
}

void Barrage::kill() {
	//for (auto b : _list) {
	//	BulletKilledEffectMgr::getIns()->regist(b->dat.x, b->dat.y, (eBulletColor)b->dat.color);
	//	delete b;
	//}
	//_list.clear();
}
