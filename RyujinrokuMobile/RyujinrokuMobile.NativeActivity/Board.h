#pragma once

#include "Drawable.h"

class Board final : public Drawable
{
public:
    Board() = default;
    ~Board() = default;
    bool update() override;
    void draw() const override;
};

