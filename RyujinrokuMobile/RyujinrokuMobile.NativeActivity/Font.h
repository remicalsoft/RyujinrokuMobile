#pragma once

#include "Singleton.h"
#include <DxLib.h>

class Font final : public Singleton<Font> {

public:
    Font() = default;
    ~Font() = default;
    void load() {
        _font13 = CreateFontToHandle("hoge", 13, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
        _font30 = CreateFontToHandle("hoge", 30, 6, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
    }
    void release() {
        DeleteFontToHandle(_font13);
        DeleteFontToHandle(_font30);
    }

    int _font13, _font30;

private:

};

