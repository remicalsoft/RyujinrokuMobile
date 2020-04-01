#include "ImageBullet.h"
#include "Macro.h"


const float WEIGHT = 0.71;
const float ImageBullet::RANGE[] = {
    5.5f * WEIGHT,//Small
    4.0f * WEIGHT,//Barrier
    4.0f * WEIGHT,//SparkSmall
    5.0f * WEIGHT,//Kome
    4.5f * WEIGHT,//Umaibo
    9.0f * WEIGHT,//SparkBig
    10.0f * WEIGHT,//Kodama	//実測12.0f
    6.5f * WEIGHT,//Yosei
    9.0f * WEIGHT,//Ring
    11.0f * WEIGHT,//Ame
    19.5f * WEIGHT,//Tama	//実測23.0f
    38.0f * WEIGHT,//Odama
    2.8f * WEIGHT,//Laser
    10.0f * WEIGHT,//Ofuda
    5.0f * WEIGHT,//Star
    6.0f * WEIGHT,//Rain
    9.0f * WEIGHT,//Rainbow
};

const float ImageBullet::SORT_Z[] = {
    3,//Small
    4,//Barrier
    4,//SparkSmall
    4,//Kome
    5,//Umaibo
    5,//SparkBig
    8,//Kodama
    8,//Yosei
    10,//Ofuda
    15,//Ring
    20,//Ame
    22,//Tama
    32,//Odama
    3,//Laser
    5,//Star
    5,//Rain
    8,//Rainbow
};

ImageBullet::ImageBullet()
{
    _sizeList.push_back(new Size(16, 16));//0
    _sizeList.push_back(new Size(28, 30));//1
    _sizeList.push_back(new Size(38, 38));//2
    _sizeList.push_back(new Size(18, 31));//3
    _sizeList.push_back(new Size(64, 64));//4
    _sizeList.push_back(new Size(76, 76));//5
    _sizeList.push_back(new Size(32, 32));//6
    _sizeList.push_back(new Size(54, 54));//7
    _sizeList.push_back(new Size(36, 36));//8
    _sizeList.push_back(new Size(30, 57));//9
    _sizeList.push_back(new Size(62, 62));//10
    _sizeList.push_back(new Size(108, 108));//11
    _sizeList.push_back(new Size(12, 240));//12
    _sizeList.push_back(new Size(28, 32));//13
    _sizeList.push_back(new Size(34, 34));//14
    _sizeList.push_back(new Size(20, 34));//15
    _sizeList.push_back(new Size(20, 20));//16
    myLoadDivGraph("bullet/00.small.png");
    myLoadDivGraph("bullet/01.barrier.png");
    myLoadDivGraph("bullet/02.sparkSmall.png");
    myLoadDivGraph("bullet/03.kome.png");
    myLoadDivGraph("bullet/04.umaibo.png");
    myLoadDivGraph("bullet/05.sparkBig.png");
    myLoadDivGraph("bullet/06.kodama.png");
    myLoadDivGraph("bullet/07.yosei.png");
    myLoadDivGraph("bullet/08.ring.png");
    myLoadDivGraph("bullet/09.ame.png");
    myLoadDivGraph("bullet/10.tama.png");
    myLoadDivGraph("bullet/11.odama.png");
    myLoadDivGraph("bullet/12.laser.png");
    myLoadDivGraph("bullet/13.ofuda.png");
    myLoadDivGraph("bullet/14.star.png");
    myLoadDivGraph("bullet/15.rain.png");
    myLoadDivGraph("bullet/16.rainbow.png");
}

/*!
@brief 弾の画像をロードして_listに格納する
*/
void ImageBullet::myLoadDivGraph(const char* fname) {
    int id = _list.size();
    Size* size = _sizeList[id];
    int *bullets = new int[eColorNum];
    LoadDivGraph(fname, eColorNum, eColorNum, 1, size->w, size->h, bullets);
    _list.push_back(bullets);
}

/*!
@brief type種別のcolor色の弾の画像ハンドルを取得
*/
int ImageBullet::get(unsigned int type, unsigned int color) const {
    if (eTypeNum <= type) {
        ERR("弾のtypeが不正です。\n");
    }
    if (eColorNum <= color) {
        ERR("弾のcolorが不正です。\n");
    }
    return _list[type][color];
}

/*!
@brief type種別の画像サイズを返す
*/
const Size* ImageBullet::getSize(unsigned int type) const {
    if (_sizeList.size() <= type) {
        ERR("wh_tのgetSizeの指定が間違っています");
    }
    return _sizeList[type];
}
