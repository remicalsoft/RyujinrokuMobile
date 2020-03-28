#pragma once

#include <list>

class Fps {

public:
    Fps();
    void wait();
    void draw() const;

private:
    std::list<int> _list;
    unsigned _counter;
    float    _fps;

    void        updateAverage();
    void        regist();
    unsigned    getWaitTime() const;

};

