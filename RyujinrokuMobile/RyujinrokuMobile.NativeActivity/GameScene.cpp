#include "GameScene.h"
#include <DxLib.h>
#include "Macro.h"
#include "Background01.h"
#include "BarrageNormal.h"

using namespace std;

const char* GameScene::ParameterTagStage = "ParameterTagStage";//パラメータのタグ「ステージ」
const char* GameScene::ParameterTagLevel = "ParameterTagLevel";//パラメータのタグ「レベル」

GameScene::GameScene(shared_ptr<Context> context, IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(context, impl, parameter)
{
    _background = make_shared<Background01>(_context);
    _board = make_shared<Board>(_context);
    _bossBarrage = make_shared<BarrageNormal>(_context, 0);
    //_backgroundSpell = make_shared<Background01spell>();
    //_player = make_shared<Player>();
    //_enemyMgr = make_shared<EnemyManager>();
}

bool GameScene::update()
{
    _background->update();
    _board->update();
    _bossBarrage->update();
    //_player->update();
    //_enemyMgr->update();
    return true;
}

void GameScene::draw() const
{
    _background->draw();
    _bossBarrage->draw();
    _board->draw();
    //_player->draw();
    //_enemyMgr->draw();
}
