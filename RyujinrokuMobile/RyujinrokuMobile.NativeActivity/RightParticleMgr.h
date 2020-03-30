#pragma once

#include "Drawable.h"
#include "RightParticle.h"
#include <list>
#include <memory>

class RightParticleMgr : public Drawable {

public:
    RightParticleMgr(std::shared_ptr<Context> context);
    virtual ~RightParticleMgr();
    bool update() override;
    void draw() const override;

private:
    int _img, _counter;
    std::list<std::shared_ptr<RightParticle>> _list;
};
