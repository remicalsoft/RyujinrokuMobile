#pragma once

#include "Drawable.h"

class View : public Drawable 
{

public:
    View(std::shared_ptr<Context> context) : Drawable(context) {

    }
    virtual ~View() = default;

};

