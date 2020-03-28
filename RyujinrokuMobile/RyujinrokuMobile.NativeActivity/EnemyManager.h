#pragma once

#include "Drawable.h"
#include <memory>
#include <list>
#include "AbstractEnemy.h"

class EnemyManager : public Drawable
{
public:
    EnemyManager();
    virtual ~EnemyManager() = default;
    bool update() override;
    void draw() const override;

private:
    std::list<std::shared_ptr<AbstractEnemy>> _list;

};

