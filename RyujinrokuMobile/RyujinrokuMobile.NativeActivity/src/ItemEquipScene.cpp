#include "ItemEquipScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Pad.h"
#include "SE.h"
#include <string>
#include "GameData.h"
#include "SavedData.h"
#include "Toast.h"

using namespace std;

const static int ITM_X = (WIN_W- 800)/2;
const static int ITM_Y = (WIN_H- 36 * eEquipItem_Num)/2;
const static int INTVL = 36;

ItemEquipScene::ItemEquipScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl)
{
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_imgCheckBoxOff = LoadGraph("dat/image/menu/shop/equip/checkboxOff.png");
	_imgCheckBoxOn  = LoadGraph("dat/image/menu/shop/equip/checkboxOn.png");
	_imgCell = LoadGraph("dat/image/menu/shop/equip/cell.png");
	_imgTitleCell = LoadGraph("dat/image/menu/shop/equip/titleCell.png");

	_fontBig = CreateFontToHandle(FONT, 29, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_font = CreateFontToHandle(FONT, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_fontSmall = CreateFontToHandle(FONT, 18, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	_infoList.push_back(new D_StoreItem("レーザーのドレス",		"ショットを切り替えて強いレーザーが撃てるようになる", 1400));
	_infoList.push_back(new D_StoreItem("輝く指輪",				"低速移動時のアイテム吸収範囲がアップ", 200));
	_infoList.push_back(new D_StoreItem("輝く指輪・改",			"低速移動時のアイテム吸収範囲が更にアップ", 2000));
	_infoList.push_back(new D_StoreItem("煌く宝石",				"アイテムゲットボーダーラインが下にさがる", 400));
	_infoList.push_back(new D_StoreItem("煌く宝石・改",			"アイテムゲットボーダーラインが更に下にさがる", 2400));
	_infoList.push_back(new D_StoreItem("避けるジャケット",		"自機の当たり判定が小さくなる(あたりにくくなる)", 1000));
	_infoList.push_back(new D_StoreItem("避けるジャケット・改",	"自機の当たり判定が更に小さくなる(あたりにくくなる)", 5000));
	_infoList.push_back(new D_StoreItem("集うフェロモン",		"敵の当たり判定が大きくなる", 200));
	_infoList.push_back(new D_StoreItem("集うフェロモン・改",	"敵の当たり判定が更に大きくなる", 2000));
	_infoList.push_back(new D_StoreItem("親父の根性魂",			"ショットがわずかに強くなる", 800));
	_infoList.push_back(new D_StoreItem("親父の根性魂・改",		"更にショットがわずかに強くなる", 4000));
	_infoList.push_back(new D_StoreItem("精霊の祝福",			"ボム数が0の時一度だけボムが使える(消耗品)", 1000));
	_infoList.push_back(new D_StoreItem("精霊の祝福・改",		"ボム数が0の時もう一度だけボムが使える(消耗品)", 1500));
	_infoList.push_back(new D_StoreItem("お色気の壺",			"どこかでアイシャが服を脱ぐようになるかもしれない(再起動後反映)", 50000));

	int color = GetColor(255, 255, 255);
	for (int i = 0; i < _infoList.size(); i++) {
		_list.push_back(new ItemFont(ITM_X+100, ITM_Y + INTVL * i+9, _infoList.at(i)->name, _font, color));
	}
	_selectID = 0;
	_list.front()->enable();
}

ItemEquipScene::~ItemEquipScene()
{
	DeleteGraph(_imgBack);
	DeleteGraph(_imgCell);
	DeleteGraph(_imgTitleCell);
	DeleteGraph(_imgCheckBoxOff);
	DeleteGraph(_imgCheckBoxOn);
	DeleteFontToHandle(_font);
	DeleteFontToHandle(_fontSmall);
	for (auto i : _list) {
		delete i;
	}
	for (auto i : _infoList) {
		delete i;
	}
}

bool ItemEquipScene::update()
{
	int money = GameData::getIns()->getMoney();
	if (Pad::getIns()->get(ePad::up) == 1 || Pad::getIns()->get(ePad::up) > 30) {
		     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + (eEquipItem_Num - 1)) % eEquipItem_Num;
		disableAll();
		_list.at(_selectID)->enable();
	}
	if (Pad::getIns()->get(ePad::down) == 1 || Pad::getIns()->get(ePad::down) > 30) {
		     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + 1) % eEquipItem_Num;
		disableAll();
		_list.at(_selectID)->enable();
	}
	if (Pad::getIns()->get(ePad::shot) == 1) {
		if (SavedData::getIns()->dat.hasEquipableItem[_selectID]) {
			if (_selectID == eEquipItem_Bomb || _selectID == eEquipItem_Bomb2) {
				SE::getIns()->setPlay(eSE::eSE_error);
				Toast::getIns()->add("装備を変更できないアイテムです");
			}
			else {
				SavedData::getIns()->dat.isEquiped[_selectID] = !SavedData::getIns()->dat.isEquiped[_selectID];
				SE::getIns()->setPlay(eSE::eSE_equip);
			}
		}
		else {
			SE::getIns()->setPlay(eSE::eSE_error);
			Toast::getIns()->add("このアイテムはまだ購入していません");
		}
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

void ItemEquipScene::draw()
{
	DrawGraph(0, 0, _imgBack, FALSE);
	DrawGraph(ITM_X, ITM_Y + INTVL * (-1), _imgTitleCell, TRUE);
	DrawStringToHandle(100, WIN_H - 50, _infoList.at(_selectID)->explanation, GetColor(255, 255, 255), _fontSmall);
	DrawStringToHandle(ITM_X + 13, ITM_Y - INTVL + 9, "装備", GetColor(200, 200, 200), _font);
	DrawStringToHandle(ITM_X + 600, ITM_Y - INTVL + 9, "所持", GetColor(200, 200, 200), _font);
	for (int i = 0; i < _infoList.size(); i++) {
		DrawGraph(ITM_X, ITM_Y + INTVL * i, _imgCell, TRUE);
		_list[i]->draw();
		int img = _imgCheckBoxOff;
		if (SavedData::getIns()->dat.isEquiped[i]) {
			img = _imgCheckBoxOn;
		}
		if (!SavedData::getIns()->dat.hasEquipableItem[i]) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		}
		DrawGraph(ITM_X + 20, ITM_Y + INTVL * i + (37 - 22) / 2-2, img, TRUE);
		if (!SavedData::getIns()->dat.hasEquipableItem[i]) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		if (SavedData::getIns()->dat.hasEquipableItem[i]) {
			DrawStringToHandle(ITM_X + 600, ITM_Y + INTVL * i + (37 - 22) / 2-3, "○", GetColor(200, 200, 200), _fontBig);
		}
		else {
			DrawStringToHandle(ITM_X + 605, ITM_Y + INTVL * i + (37 - 22) / 2-3, "-", GetColor(200, 200, 200), _fontBig);
		}
	}
}

void ItemEquipScene::disableAll()
{
	for (auto i : _list) {
		i->disable();
	}
}
