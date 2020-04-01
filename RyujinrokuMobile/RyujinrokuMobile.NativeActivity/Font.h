#pragma once

#include "Singleton.h"
#include <DxLib.h>

class Font final : public Singleton<Font> {

public:
    Font() = default;
    ~Font() = default;
    void load() {
        _font24  = CreateFontToHandle("hoge",  24, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
        _font48  = CreateFontToHandle("hoge",  48, 6, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
        _font100 = CreateFontToHandle("hoge", 100, 6, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
    }
    void release() {
        DeleteFontToHandle(_font24);
        DeleteFontToHandle(_font48);
        DeleteFontToHandle(_font100);
    }

    int _font24, _font48, _font100;

private:

};

