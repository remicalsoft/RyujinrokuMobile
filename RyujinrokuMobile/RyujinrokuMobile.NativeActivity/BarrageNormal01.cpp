//#include "Define.h"
//#include <math.h>
//#include "BarrageNormal.h"
//#include <DxLib.h>
//#include "MathUtils.h"
////#include "ImageBullet.h"
////#include "SE.h"
////#include "Calculator.h"
////#include "Utils.h"
//
//using namespace std;
//
//void BarrageNormal::Barrage000() {
//	if (_counter % 2 == 0) {
//		bullet_t dat;
//		dat.x = Define::FIELD_W/2;
//		dat.y = Define::FIELD_W/5;
//		dat.ang = randf2(PI);
//		dat.v = 5+randf2(1);
//		dat.type = eBulletType::eTama;
//		dat.color = eBulletColor::eBlue;
//		_list.push_back(make_shared<Bullet>(_context, &dat));
//		//		SE::getIns()->setPlay(eSE::eSE_enemyShot);
//	}
//	for (auto b : _list) {
//		if (b->dat.counter < 60) {
//			b->dat.v -= 0.2f;
//		}
//	}
//}
//
//void BarrageNormal::Barrage001() {}
//void BarrageNormal::Barrage002() {}
//void BarrageNormal::Barrage003() {}
//void BarrageNormal::Barrage004() {}
//void BarrageNormal::Barrage005() {}
//void BarrageNormal::Barrage006() {}
//void BarrageNormal::Barrage007() {}
//void BarrageNormal::Barrage008() {}
//void BarrageNormal::Barrage009() {}
//void BarrageNormal::Barrage010() {}
//void BarrageNormal::Barrage011() {}
//void BarrageNormal::Barrage012() {}
//void BarrageNormal::Barrage013() {}
//void BarrageNormal::Barrage014() {}
//void BarrageNormal::Barrage015() {}
//void BarrageNormal::Barrage016() {}
//void BarrageNormal::Barrage017() {}
//void BarrageNormal::Barrage018() {}
//void BarrageNormal::Barrage019() {}
//void BarrageNormal::Barrage020() {}
//void BarrageNormal::Barrage021() {}
//void BarrageNormal::Barrage022() {}
//void BarrageNormal::Barrage023() {}
//void BarrageNormal::Barrage024() {}
//void BarrageNormal::Barrage025() {}
//void BarrageNormal::Barrage026() {}
//void BarrageNormal::Barrage027() {}
//void BarrageNormal::Barrage028() {}
//void BarrageNormal::Barrage029() {}
//void BarrageNormal::Barrage030() {}
//void BarrageNormal::Barrage031() {}
//void BarrageNormal::Barrage032() {}
//void BarrageNormal::Barrage033() {}
//void BarrageNormal::Barrage034() {}
//void BarrageNormal::Barrage035() {}
//void BarrageNormal::Barrage036() {}
//void BarrageNormal::Barrage037() {}
//void BarrageNormal::Barrage038() {}
//void BarrageNormal::Barrage039() {}
//void BarrageNormal::Barrage040() {}
//void BarrageNormal::Barrage041() {}
//void BarrageNormal::Barrage042() {}
//void BarrageNormal::Barrage043() {}
//void BarrageNormal::Barrage044() {}
//void BarrageNormal::Barrage045() {}
//void BarrageNormal::Barrage046() {}
//void BarrageNormal::Barrage047() {}
//void BarrageNormal::Barrage048() {}
//void BarrageNormal::Barrage049() {}
//void BarrageNormal::Barrage050() {}
//void BarrageNormal::Barrage051() {}
//void BarrageNormal::Barrage052() {}
//void BarrageNormal::Barrage053() {}
//void BarrageNormal::Barrage054() {}
//void BarrageNormal::Barrage055() {}
//void BarrageNormal::Barrage056() {}
//void BarrageNormal::Barrage057() {}
//void BarrageNormal::Barrage058() {}
//void BarrageNormal::Barrage059() {}
//void BarrageNormal::Barrage060() {}
//void BarrageNormal::Barrage061() {}
//void BarrageNormal::Barrage062() {}
//void BarrageNormal::Barrage063() {}
//void BarrageNormal::Barrage064() {}
//void BarrageNormal::Barrage065() {}
//void BarrageNormal::Barrage066() {}
//void BarrageNormal::Barrage067() {}
//void BarrageNormal::Barrage068() {}
//void BarrageNormal::Barrage069() {}
//void BarrageNormal::Barrage070() {}
//void BarrageNormal::Barrage071() {}
//void BarrageNormal::Barrage072() {}
//void BarrageNormal::Barrage073() {}
//void BarrageNormal::Barrage074() {}
//void BarrageNormal::Barrage075() {}
//void BarrageNormal::Barrage076() {}
//void BarrageNormal::Barrage077() {}
//void BarrageNormal::Barrage078() {}
//void BarrageNormal::Barrage079() {}
//void BarrageNormal::Barrage080() {}
//void BarrageNormal::Barrage081() {}
//void BarrageNormal::Barrage082() {}
//void BarrageNormal::Barrage083() {}
//void BarrageNormal::Barrage084() {}
//void BarrageNormal::Barrage085() {}
//void BarrageNormal::Barrage086() {}
//void BarrageNormal::Barrage087() {}
//void BarrageNormal::Barrage088() {}
//void BarrageNormal::Barrage089() {}
//void BarrageNormal::Barrage090() {}
//void BarrageNormal::Barrage091() {}
//void BarrageNormal::Barrage092() {}
//void BarrageNormal::Barrage093() {}
//void BarrageNormal::Barrage094() {}
//void BarrageNormal::Barrage095() {}
//void BarrageNormal::Barrage096() {}
//void BarrageNormal::Barrage097() {}
//void BarrageNormal::Barrage098() {}
//void BarrageNormal::Barrage099() {}
