#pragma once

// フレームごとに更新するクラスは全てのクラスを継承する
class Task {

public:
    Task() = default;
    virtual ~Task() = default;
    virtual bool update()     = 0; //返り値 true=正常終了 false=これ以上更新不要

};
