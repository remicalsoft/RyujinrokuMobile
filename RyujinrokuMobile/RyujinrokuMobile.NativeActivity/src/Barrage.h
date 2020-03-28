#pragma once

#include <list>
#include "Bullet.h"
#include "Player.h"
#include "BulletEffectRegistable.h"

class Barrage
{

protected:
	std::list<Bullet*> _list;
	float _angle;
	float _passedX;
	float _passedY;
	float _baseAngle[100];
	float _baseX[100];
	float _baseY[100];
	float _remValue[100];
	int _remCounter;
	int _counter;
	bool _isDone;
	int _n;

	typedef void(Barrage::*FUNC)();
	std::vector<FUNC> _funcList;

	virtual void Barrage000() = 0;
	virtual void Barrage001() = 0;
	virtual void Barrage002() = 0;
	virtual void Barrage003() = 0;
	virtual void Barrage004() = 0;
	virtual void Barrage005() = 0;
	virtual void Barrage006() = 0;
	virtual void Barrage007() = 0;
	virtual void Barrage008() = 0;
	virtual void Barrage009() = 0;
	virtual void Barrage010() = 0;
	virtual void Barrage011() = 0;
	virtual void Barrage012() = 0;
	virtual void Barrage013() = 0;
	virtual void Barrage014() = 0;
	virtual void Barrage015() = 0;
	virtual void Barrage016() = 0;
	virtual void Barrage017() = 0;
	virtual void Barrage018() = 0;
	virtual void Barrage019() = 0;
	virtual void Barrage020() = 0;
	virtual void Barrage021() = 0;
	virtual void Barrage022() = 0;
	virtual void Barrage023() = 0;
	virtual void Barrage024() = 0;
	virtual void Barrage025() = 0;
	virtual void Barrage026() = 0;
	virtual void Barrage027() = 0;
	virtual void Barrage028() = 0;
	virtual void Barrage029() = 0;
	virtual void Barrage030() = 0;
	virtual void Barrage031() = 0;
	virtual void Barrage032() = 0;
	virtual void Barrage033() = 0;
	virtual void Barrage034() = 0;
	virtual void Barrage035() = 0;
	virtual void Barrage036() = 0;
	virtual void Barrage037() = 0;
	virtual void Barrage038() = 0;
	virtual void Barrage039() = 0;
	virtual void Barrage040() = 0;
	virtual void Barrage041() = 0;
	virtual void Barrage042() = 0;
	virtual void Barrage043() = 0;
	virtual void Barrage044() = 0;
	virtual void Barrage045() = 0;
	virtual void Barrage046() = 0;
	virtual void Barrage047() = 0;
	virtual void Barrage048() = 0;
	virtual void Barrage049() = 0;
	virtual void Barrage050() = 0;
	virtual void Barrage051() = 0;
	virtual void Barrage052() = 0;
	virtual void Barrage053() = 0;
	virtual void Barrage054() = 0;
	virtual void Barrage055() = 0;
	virtual void Barrage056() = 0;
	virtual void Barrage057() = 0;
	virtual void Barrage058() = 0;
	virtual void Barrage059() = 0;
	virtual void Barrage060() = 0;
	virtual void Barrage061() = 0;
	virtual void Barrage062() = 0;
	virtual void Barrage063() = 0;
	virtual void Barrage064() = 0;
	virtual void Barrage065() = 0;
	virtual void Barrage066() = 0;
	virtual void Barrage067() = 0;
	virtual void Barrage068() = 0;
	virtual void Barrage069() = 0;
	virtual void Barrage070() = 0;
	virtual void Barrage071() = 0;
	virtual void Barrage072() = 0;
	virtual void Barrage073() = 0;
	virtual void Barrage074() = 0;
	virtual void Barrage075() = 0;
	virtual void Barrage076() = 0;
	virtual void Barrage077() = 0;
	virtual void Barrage078() = 0;
	virtual void Barrage079() = 0;
	virtual void Barrage080() = 0;
	virtual void Barrage081() = 0;
	virtual void Barrage082() = 0;
	virtual void Barrage083() = 0;
	virtual void Barrage084() = 0;
	virtual void Barrage085() = 0;
	virtual void Barrage086() = 0;
	virtual void Barrage087() = 0;
	virtual void Barrage088() = 0;
	virtual void Barrage089() = 0;
	virtual void Barrage090() = 0;
	virtual void Barrage091() = 0;
	virtual void Barrage092() = 0;
	virtual void Barrage093() = 0;
	virtual void Barrage094() = 0;
	virtual void Barrage095() = 0;
	virtual void Barrage096() = 0;
	virtual void Barrage097() = 0;
	virtual void Barrage098() = 0;
	virtual void Barrage099() = 0;

	void calcIsHit();
	void calcIsGraze();

	IPlayerInfoGettable* _implPlayerInfoGettable;
	BulletEffectRegistable* _implBulletEffect;
public:
	Barrage(IPlayerInfoGettable* impl, BulletEffectRegistable* implBulletDisappearEffectRegistable);
	virtual ~Barrage();
	virtual bool update();
	virtual void draw()=0;
	void setFunc();
	void kill();
	int getCounter() { return _counter; };
};

