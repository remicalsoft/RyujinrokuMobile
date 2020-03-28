#pragma once

class Pos final
{
public:
    Pos() :_x(0), _y(0) {}
    Pos(int x, int y):_x(x),_y(y){}
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    int getX() { return _x; }
    int getY() { return _y; }
private:
    int _x;
    int _y;
};

