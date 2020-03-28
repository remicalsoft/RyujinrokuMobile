#include "StoreBuyKeyScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Pad.h"
#include "SE.h"
#include <string>

using namespace std;

enum eEquipItem {
	eEquipItem_Dress,
	eEquipItem_Ring,
	eEquipItem_Ring2,
	eEquipItem_Hoseki,
	eEquipItem_Hoseki2,
	eEquipItem_Jacket,
	eEquipItem_Jacket2,
	eEquipItem_Pheromone,
	eEquipItem_Pheromone2,
	eEquipItem_Soul,
	eEquipItem_Soul2,
	eEquipItem_Tsubo,

	eEquipItem_Num
};

const static int ITM_X = 200;
const static int ITM_Y = 150;
const static int INTVL = 50;

StoreBuyKeyScene::StoreBuyKeyScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl)
{
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_font      = CreateFontToHandle(FONT, 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_fontSmall = CreateFontToHandle(FONT, 18, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	_infoList.push_back(new D_StoreItem("神秘のドレス",			"好きな時に変身し性質の違う強いショットが撃てるようになる（未実装）", 100));
	_infoList.push_back(new D_StoreItem("輝く指輪",				"低速移動時のアイテム吸収範囲がアップ", 100));
	_infoList.push_back(new D_StoreItem("魅惑の指輪",			"低速移動時のアイテム吸収範囲が更にアップ", 1000));
	_infoList.push_back(new D_StoreItem("輝く宝石",				"アイテムゲットボーダーラインが下にさがる", 100));
	_infoList.push_back(new D_StoreItem("魅惑の宝石",			"アイテムゲットボーダーラインが更に下にさがる", 1000));
	_infoList.push_back(new D_StoreItem("輝くジャケット",		"自機の当たり判定が小さくなる(あたりにくくなる)", 100));
	_infoList.push_back(new D_StoreItem("魅惑のジャケット",		"自機の当たり判定が更に小さくなる(あたりにくくなる)", 1000));
	_infoList.push_back(new D_StoreItem("輝くフェロモン",		"敵の当たり判定が大きくなる", 100));
	_infoList.push_back(new D_StoreItem("魅惑のフェロモン",		"敵の当たり判定が更に大きくなる", 1000));
	_infoList.push_back(new D_StoreItem("輝く親父の根性魂",		"食らいボム判定時間が長くなる", 100));
	_infoList.push_back(new D_StoreItem("魅惑の親父の根性魂",	"食らいボム判定時間が更に長くなる", 1000));
	_infoList.push_back(new D_StoreItem("お色気の壺",			"あるシーンでアイシャが服を脱ぐようになる", 50000));

	int color = GetColor(255, 255, 255);
	for (int i = 0; i < _infoList.size(); i++) {
		_list.push_back(new ItemFont(ITM_X, ITM_Y + INTVL * i, _infoList.at(i)->name, _font, color));
	}
	_selectID = 0;
	_list.front()->enable();
}

StoreBuyKeyScene::~StoreBuyKeyScene()
{
	DeleteGraph(_imgBack);
	DeleteFontToHandle(_font);
	DeleteFontToHandle(_fontSmall);
	for (auto i : _list) {
		delete i;
	}
	for (auto i : _infoList) {
		delete i;
	}
}

bool StoreBuyKeyScene::update()
{
	if (Pad::getIns()->get(ePad::up) == 1) {
		     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + (eEquipItem_Num - 1)) % eEquipItem_Num;
		disableAll();
		_list.at(_selectID)->enable();
	}
	if (Pad::getIns()->get(ePad::down) == 1) {
		     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + 1) % eEquipItem_Num;
		disableAll();
		_list.at(_selectID)->enable();
	}
	if (Pad::getIns()->get(ePad::shot) == 1) {
	}
	if (Pad::getIns()->get(ePad::bom) == 1) {
		SE::getIns()->setPlay(eSE::eSE_cancel);
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
		return false;
	}
	for (auto i : _list) {
		i->update();
	}
	return true;
}

void StoreBuyKeyScene::draw()
{
	DrawGraph(0, 0, _imgBack, FALSE);
	for(auto i : _list)
	{
		i->draw();
	}
	DrawStringToHandle(100, WIN_H - 50, _infoList.at(_selectID)->explanation, GetColor(255, 255, 255), _fontSmall);
	for (int i = 0; i < _infoList.size(); i++) {
		string str;
		str += std::to_string(_infoList.at(i)->price) + "円";
		DrawStringToHandle(ITM_X+500, ITM_Y + INTVL * i, str.c_str(), GetColor(200,200,200), _fontSmall);
	}
}

void StoreBuyKeyScene::disableAll()
{
	for (auto i : _list) {
		i->disable();
	}
}
