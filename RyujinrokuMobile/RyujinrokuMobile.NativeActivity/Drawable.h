#pragma once

#include "Task.h"
#include <memory>
#include "Context.h"

// 描画可能な物全てはこのクラスを継承する
class Drawable : public Task {

protected:
    int _layer; //描画されるレイヤー
    int _type;  //レイヤーの中で描画される順番(レイヤー内種類)(弾に使う)
    int _z;     //typeの中のz座標(描画される順番)
    std::shared_ptr<Context> _context;

public:
    Drawable(std::shared_ptr<Context> context):_context(context){}
    virtual ~Drawable() = default;
    virtual void draw() const = 0; // 描画メソッドの中でメンバ変数を変更してはならない(const method)

    enum eLayer {

    };

};

