#include "TitleScene.h"
#include <DxLib.h>
#include "GameScene.h"
#include "Define.h"

using namespace std;

TitleScene::TitleScene(shared_ptr<Context> context, IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(context, impl, parameter)
{
    _imgBack = LoadGraph("menu.back.png");
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 300,  900   , "ゲームスタート", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 300, 1000+10, "プラクティス", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 300, 1100+20, "アイテムショップ", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 300, 1200+30, "リプレイ", this));
    _buttonList.emplace_back(make_shared<MenuButton>(_context, 300, 1300+40, "設定", this));
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
    return true;
}

void TitleScene::draw() const{

    DrawGraph(0, 0, _imgBack, FALSE);
    for (auto b : _buttonList) {
        b->draw();
    }
}

void TitleScene::onClick(View view)
{
}
