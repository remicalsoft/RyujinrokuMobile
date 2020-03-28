#pragma once

#include "Drawable.h"

class Player : public Drawable
{
public:
    Player();
    virtual ~Player() = default;
    bool update() override;
    void draw() const override;

private:
    void move();

    float _x, _y;   //座標
};

