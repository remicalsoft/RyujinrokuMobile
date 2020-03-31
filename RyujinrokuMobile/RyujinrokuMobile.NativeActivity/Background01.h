#pragma once

#include <list>
#include <memory>
#include <array>
#include "Surface.h"
#include "Drawable.h"

class Background01 final : public Drawable
{

public:
    Background01(std::shared_ptr<Context> context);
    ~Background01();
    bool update() override;
    void draw() const override;

private:
    void draw(VECTOR offset) const;

    std::list<std::shared_ptr<Surface>> _list;
    std::array<int, Surface::DATANUM> _handle;
};
