#pragma once

#include "Singleton.h"
#include <vector>
#include <array>

class Image final : public Singleton<Image> {

public:
    Image() = default;
    ~Image() = default;
    void load();
    void release();

    int _menuButtonLeft, _menuButtonMiddle, _menuButtonRight;
    int _player;
    int _board;
    int _fusuma, _floor;
    int _backSpell00, _backSpell01;
    int _enemySmall[2];
    int _enemyNormal[9];
    int _enemyBig[9];

private:
    std::vector<int> _images;

    int myLoadGraph(const char*);
    int myLoadDivGraph(const char *fileName, int n, int xn, int yn, int w, int h, int* buf);

};

