#include "TitleScene.h"
#include <DxLib.h>
#include "GameScene.h"
#include "Define.h"

using namespace std;

TitleScene::TitleScene(shared_ptr<Context> context, IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(context, impl, parameter)
{
    _maskAddBlendValue = 0;
    _counter = 0;
    _imgBack = LoadGraph("menu.back.png");
    _imgBackMask = LoadGraph("manu.back_mask.png");
    _buttonList.emplace_back(make_shared<MenuButton>(_context,  36, 1100 + 160 * 3, "ゲームスタート", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context,  36, 1100 + 160 * 4, "プラクティス", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context,  36, 1100 + 160 * 5, "アイテムショップ", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 540, 1100 + 160 * 3, "リプレイ", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 540, 1100 + 160 * 4, "ストーリー", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 540, 1100 + 160 * 5, "設定", this));
    for (auto b : _buttonList) {
        b->setStrDrawWidth(384);
    }
}

TitleScene::~TitleScene() {
    DeleteGraph(_imgBack);
    DeleteGraph(_imgBackMask);
}

bool TitleScene::update()
{
    //if (Pad::getIns()->get(ePad::shot) == 1) {
    //    Parameter parameter;
    //    parameter.set(GameScene::ParameterTagLevel, Define::eLevel::Easy);
    //    const bool stackClear = false;
    //    _implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
    //    return false;
    //}
    //if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
    //    Parameter parameter;
    //    parameter.set(GameScene::ParameterTagLevel, Define::eLevel::Normal);
    //    const bool stackClear = false;
    //    _implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
    //    return false;
    //}
    for (auto b : _buttonList) {
        b->update();
    }
    if ((_counter / 4) % 2 == 0) {
        _maskAddBlendValue = 55 + GetRand(200);
    }
    _counter++;
    return true;
}

void TitleScene::draw() const
{
    DrawGraph(0, 0, _imgBack, FALSE);
    SetDrawBlendMode(DX_BLENDMODE_ADD, _maskAddBlendValue);
    DrawGraph(0, 0, _imgBackMask, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    for (auto b : _buttonList) {
        b->draw();
    }
}

void TitleScene::onClick(View* view)
{
}
