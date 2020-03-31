#pragma once

#include <memory>

#include "Context.h"
#include "AbstractScene.h"
#include "Board.h"

//#include "Player.h"
//#include "EnemyManager.h"

class GameScene : public AbstractScene
{
public:
    const static char* ParameterTagStage;//パラメータのタグ「ステージ」
    const static char* ParameterTagLevel;//パラメータのタグ「レベル」

    GameScene(std::shared_ptr<Context> context, IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~GameScene() = default;

    bool update() override;
    void draw() const override;

private:
    //std::shared_ptr<Player> _player;
    std::shared_ptr<Board>  _board;
    std::shared_ptr<Drawable> _background;
    //std::shared_ptr<AbstractBackground> _backgroundSpell;
    //std::shared_ptr<EnemyManager> _enemyMgr;
};

