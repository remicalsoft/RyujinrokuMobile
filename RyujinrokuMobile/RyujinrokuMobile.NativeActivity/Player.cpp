#include "Player.h"
#include "Pad.h"
#include <DxLib.h>
#include "Image.h"
#include "Define.h"

const static float SPEED = 9;

Player::Player() : 
    _x((float)CENTER_X),
    _y((float)Define::FIELD_H*0.8f)
{
}

bool Player::update()
{
    move();
    return true;
}

void Player::draw() const
{
    DrawRotaGraphF(_x, _y, 1.0, 0.0, Image::getIns()->getPlayer(), TRUE);
}

/*!
@brief プレイヤーを動かす
*/
void Player::move()
{
    float moveX = 0, moveY = 0;
    if (Pad::getIns()->get(ePad::left) > 0) {
        moveX -= SPEED;
    }
    if (Pad::getIns()->get(ePad::right) > 0) {
        moveX += SPEED;
    }
    if (Pad::getIns()->get(ePad::down) > 0) {
        moveY += SPEED;
    }
    if (Pad::getIns()->get(ePad::up) > 0) {
        moveY -= SPEED;
    }
    if (moveX && moveY) { //斜め移動
        moveX /= (float)sqrt(2.0);
        moveY /= (float)sqrt(2.0);
    }
    if (Pad::getIns()->get(ePad::slow) > 0) {//低速移動
        moveX /= 3;
        moveY /= 3;
    }
    if (moveX + _x < Define::IN_X) {//左枠より左なら
        _x = (float)Define::IN_X;   //左枠で止める
    }
    else if (moveX + _x > Define::IN_X + Define::IN_W) {//右枠より右なら
        _x = (float)(Define::IN_X + Define::IN_W);      //右枠で止める
    }
    else {//枠内なら
        _x += moveX;//普通に移動
    }
    if (moveY + _y < Define::IN_Y) {   //上枠より上なら
        _y = (float)Define::IN_Y;      //上枠で止める
    }
    else if (moveY + _y > Define::IN_Y + Define::IN_H) {    //下枠より下なら
        _y = (float)(Define::IN_Y + Define::IN_H);          //下枠で止める
    }
    else {//枠内なら
        _y += moveY;//普通に移動
    }
}