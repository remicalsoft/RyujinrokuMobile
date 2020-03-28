#pragma once

#include "IOnSceneChangedListener.h"
#include "Parameter.h"
#include "Drawable.h"

class IOnSceneChangedListener;

class AbstractScene : public Drawable
{
protected:
    IOnSceneChangedListener* _implSceneChanged;

public:
    AbstractScene(std::shared_ptr<Context> context, IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~AbstractScene() = default;
};
