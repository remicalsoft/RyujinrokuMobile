#pragma once

#include <list>
#include "Drawable.h"

class Fps : public Drawable {

public:
    Fps(std::shared_ptr<Context> context);
    bool update() override ;
    void draw() const override ;

private:
    std::list<int> _list;
    unsigned _counter;
    float    _fps;

    void        updateAverage();
    void        regist();
    unsigned    getWaitTime() const;

};

