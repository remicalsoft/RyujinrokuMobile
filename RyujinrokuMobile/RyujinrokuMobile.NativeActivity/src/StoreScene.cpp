#include "StoreScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Pad.h"
#include "SE.h"
#include "Toast.h"

enum eStoreItem {
	eStoreItem_BuyEquiq,
	eStoreItem_BuyKey,
	eStoreItem_Equip,

	eStoreItem_Num
};

const static char* itemNames[] = {
	"装備を買う",
	"オマケ弾幕解放の鍵を買う",
	"装備を変更する"
};

StoreScene::StoreScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl)
{
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_font = CreateFontToHandle(FONT, 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_list.push_back(new ItemFont(200, 150, itemNames[0], _font, GetColor(255, 255, 255)));
	_list.push_back(new ItemFont(200, 200, itemNames[1], _font, GetColor(255, 255, 255)));
	_list.push_back(new ItemFont(200, 250, itemNames[2], _font, GetColor(255, 255, 255)));

	_selectID = 0;
	_list.front()->enable();
}

StoreScene::~StoreScene()
{
	DeleteGraph(_imgBack);
	DeleteFontToHandle(_font);
	for (auto i : _list) {
		delete i;
	}
}

bool StoreScene::update()
{
	if (Pad::getIns()->get(ePad::up) == 1) {
		     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + (eStoreItem_Num - 1)) % eStoreItem_Num;
		disableAll();
		_list.at(_selectID)->enable();
	}
	if (Pad::getIns()->get(ePad::down) == 1) {
		     SE::getIns()->setPlay(eSE::eSE_upDown);
		_selectID = (_selectID + 1) % eStoreItem_Num;
		disableAll();
		_list.at(_selectID)->enable();
	}
	if (Pad::getIns()->get(ePad::shot) == 1) {
		switch(_selectID){
		case 0:
			SE::getIns()->setPlay(eSE::eSE_select);
			_implSceneChanged->onSceneChanged(eScene::StoreBuy, true, nullptr);
			break;
		case 1:
			Toast::getIns()->add("バージョンアップで近日実装されます");
			SE::getIns()->setPlay(eSE::eSE_error);
			break;
		case 2:
			SE::getIns()->setPlay(eSE::eSE_select);
			_implSceneChanged->onSceneChanged(eScene::ItemEquip, true, nullptr);
			break;
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

void StoreScene::draw()
{
	DrawGraph(0, 0, _imgBack, FALSE);
	for(auto i : _list)
	{
		i->draw();
	}
}

void StoreScene::disableAll()
{
	for (auto i : _list) {
		i->disable();
	}
}
