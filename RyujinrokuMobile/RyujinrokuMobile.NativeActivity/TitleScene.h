#pragma once

#include "AbstractScene.h"
#include "MenuButton.h"
#include <list>
#include <memory>
#include "IOnClickListener.h"

class TitleScene : public AbstractScene, public IOnClickListener
{
public:
    TitleScene(std::shared_ptr<Context> context, IOnSceneChangedListener *impl, const Parameter& parameter);
    virtual ~TitleScene();
    bool update() override;
    void draw() const override;
    void onClick(View* view);

private:
    int _imgBack, _imgBackMask;
    int _maskAddBlendValue;
    int _counter;
    std::list<std::shared_ptr<MenuButton>> _buttonList;

};
