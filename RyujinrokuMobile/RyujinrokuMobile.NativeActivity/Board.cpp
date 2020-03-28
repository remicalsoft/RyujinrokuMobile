#include "Board.h"
#include "Define.h"
#include <DxLib.h>
#include "Image.h"

bool Board::update()
{
    return true;
}

void Board::draw() const
{
    DrawGraph(Define::FIELD_W, 0, Image::getIns()->getBoard(), TRUE);
}
