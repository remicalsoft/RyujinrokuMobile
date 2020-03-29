#include "TouchEvent.h"
#include "DxLib.h"

void TouchEvent::update()
{
    _prePos = _pos;
    // 現在タッチしている指の数を取得
    _touchNum = GetTouchInputNum();
    // 以下の計算はタッチ数2個より多く計算しない
    int n = _touchNum > _pos.size() ? _pos.size() : _touchNum;
    for (int i = 0; i < n; i++) {
        int x, y;
        GetTouchInput(i, &x, &y, NULL, NULL);
        _pos[i].setX(x);
        _pos[i].setY(y);
        _pressingCount[i]++;
        _releasingCount[i] = 0;
    }
    // タッチしていなければ-1をいれる
    for (int i = n; i < _pos.size(); i++) {
        _pos[i].setX(-1);
        _pos[i].setY(-1);
        _pressingCount[i] = 0;
        _releasingCount[i]++;
    }
    if (_touchNum == 1) {
        _history.emplace_back(_pos[0]);
    }
    else {
        _history.clear();
    }
}

// id個目の指の位置を取得する
Pos TouchEvent::getPos(int id) const
{
    return _pos[id];
}

Pos TouchEvent::getPrePos(int id) const
{
    return _prePos[id];
}
