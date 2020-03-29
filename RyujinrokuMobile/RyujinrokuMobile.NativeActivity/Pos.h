#pragma once

class Pos final
{
public:
    Pos() :_x(0), _y(0) {}
    Pos(int x, int y):_x(x),_y(y){}
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    int getX() const { return _x; }
    int getY() const { return _y; }

    Pos operator =(Pos* pos) {
        this->_x = pos->getX();
        this->_y = pos->getY();
        return *this;
    }
    Pos& operator =(const Pos& r)
    {
        _x = r.getX();
        _y = r.getY();
        return *this;
    }

private:
    int _x;
    int _y;
};

