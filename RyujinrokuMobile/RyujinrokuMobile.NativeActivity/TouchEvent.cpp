#include "TouchEvent.h"
#include "DxLib.h"

void TouchEvent::update()
{
    // 現在タッチしている指の数を取得
    _touchNum = GetTouchInputNum();
    // 以下の計算はタッチ数2個より多く計算しない
    int n = _touchNum > 2 ? 2 : _touchNum;
    for (int i = 0; i < n; i++) {
        int x, y;
        GetTouchInput(i, &x, &y, NULL, NULL);
        _pos[i].setX(x);
        _pos[i].setY(y);
    }
    // タッチしていなければ-1をいれる
    for (int i = n; i < 2; i++) {
        _pos[i].setX(-1);
        _pos[i].setY(-1);
    }
}

// id個目の指の位置を取得する
const Pos TouchEvent::getPos(int id) const
{
    // 指は最大2つまでしか計算しない
    if (id < 0 || 1 < id) {
        return Pos(-1, -1);
    }
    return _pos[id];
}
