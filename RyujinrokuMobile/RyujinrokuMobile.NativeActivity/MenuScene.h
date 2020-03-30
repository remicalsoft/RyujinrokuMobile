#pragma once

#include "AbstractScene.h"
#include "MenuButton.h"
#include <list>
#include <memory>
#include "IOnClickListener.h"
#include "RightParticleMgr.h"
#include "ShineLineMgr.h"

class MenuScene : public AbstractScene, public IOnClickListener
{
public:
    MenuScene(std::shared_ptr<Context> context, IOnSceneChangedListener *impl, const Parameter& parameter);
    virtual ~MenuScene();
    bool update() override;
    void draw() const override;
    void onClick(View* view) override;

private:
    int _imgBack, _imgBackMask;
    int _maskAddBlendValue;
    int _counter;
    std::list<std::shared_ptr<MenuButton>> _buttonList;
    std::shared_ptr<RightParticleMgr> _rightParticleMgr;
    std::shared_ptr<ShineLineMgr> _shineLineMgr;
};
