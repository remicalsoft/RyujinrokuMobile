#pragma once

#include <math.h>

#define PI M_PI

class Define final {

public:
    const static int WIN_W;    //ウィンドウサイズ横
    const static int WIN_H;    //ウィンドウサイズ縦

    const static int FIELD_W; //プレイヤーの移動領域幅
    const static int FIELD_H; //プレイヤーの移動領域高さ

    const static int CENTER_X; //移動領域の中心X座標
    const static int CENTER_Y; //移動領域の中心Y座標


    enum eStage {
        Stage1,
        Stage2,
        Stage3,
        Stage4,
        Stage5,
        StageEX,
        StageNum,
    };

    enum eLevel {
        Easy,
        Normal,
        LevelNum
    };

};
