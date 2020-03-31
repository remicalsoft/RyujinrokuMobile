#include "Board.h"
#include "Define.h"
#include <DxLib.h>

Board::Board(std::shared_ptr<Context> context) : Drawable(context)
{
    _img = LoadGraph("game.board.png");
}

Board::~Board()
{
    DeleteGraph(_img);
}

bool Board::update()
{
    return true;
}

void Board::draw() const
{
    DrawGraph(0, Define::FIELD_H, _img, FALSE);
}
