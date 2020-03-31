#pragma once

#include "Drawable.h"

class Board final : public Drawable
{
public:
    Board(std::shared_ptr<Context> context);
    ~Board();
    bool update() override;
    void draw() const override;

private:
    int _img;

};

