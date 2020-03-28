#include "ReplayCell.h"
#include <DxLib.h>
#include "ReplaySceneCellUtils.h"
#include "Utils.h"
#include <string>

using namespace std;

ReplayCell::ReplayCell(int x, int y, int id, int img, int imgSelected, int font)
{
	_x = x;
	_y = y;
	_id = id;
	_isActivated = false;
	_img = img;
	_imgSelected = imgSelected;
	_font = font;
	sprintf(_fileName, "リプレイデータ/%03d.rpy", id);
	string path = Utils::getSavePath();
	path += _fileName;
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		_header = nullptr;
	}
	else {
		_header = new ReplayHeader();
		fread(_header, sizeof(ReplayHeader), 1, fp);
		fclose(fp);
	}
}

ReplayCell::~ReplayCell()
{
	if (_header != nullptr) {
		delete _header;
	}
}

bool ReplayCell::update()
{

	return true;
}


void ReplayCell::draw()
{
	if (_isActivated) {
		DrawGraph(_x, _y, _imgSelected, TRUE);
	}
	else {
		DrawGraph(_x, _y, _img, TRUE);
	}
	const static int Y = 10;
	DrawFormatStringToHandle(_x +  4,           _y + Y, GetColor(220, 220, 220), _font, "%03d", _id);
	if (_header == nullptr) {
		return;
	}
	DrawFormatStringToHandle(_x + 43,           _y + Y, GetColor(220, 220, 220), _font, _header->name);
	DrawFormatStringToHandle(_x + 348 + 31 * 0, _y + Y, GetColor(220, 220, 220), _font, is1On(_header) ? "〇" : "");
	DrawFormatStringToHandle(_x + 348 + 31 * 1, _y + Y, GetColor(220, 220, 220), _font, is2On(_header) ? "〇" : "");
	DrawFormatStringToHandle(_x + 348 + 31 * 2, _y + Y, GetColor(220, 220, 220), _font, is3On(_header) ? "〇" : "");
	DrawFormatStringToHandle(_x + 348 + 31 * 3, _y + Y, GetColor(220, 220, 220), _font, is4On(_header) ? "〇" : "");
	DrawFormatStringToHandle(_x + 348 + 31 * 4, _y + Y, GetColor(220, 220, 220), _font, is5On(_header) ? "〇" : "");
	DrawFormatStringToHandle(_x + 348 + 31 * 5, _y + Y, GetColor(220, 220, 220), _font, is6On(_header) ? "〇" : "");
	DrawFormatStringToHandle(_x + 348 + 31 * 6, _y + Y, GetColor(220, 220, 220), _font, is7On(_header) ? "〇" : "");
	DrawFormatStringToHandle(_x + 348 + 31 * 7, _y + Y, GetColor(220, 220, 220), _font, _header->isSpellPractice?"〇":"");
	DrawFormatStringToHandle(_x + 593,          _y + Y, GetColor(220, 220, 220), _font, "%02d分%02d秒", _header->playTime/1000/60, (_header->playTime/1000)%60);
	DrawFormatStringToHandle(_x + 682,          _y + Y, GetColor(220, 220, 220), _font, "%03d", _header->hitCount);
	DrawFormatStringToHandle(_x + 726,          _y + Y, GetColor(220, 220, 220), _font, "%03d", _header->bombCount);
	DrawFormatStringToHandle(_x + 780,          _y + Y, GetColor(220, 220, 220), _font, "%09d", _header->score);
	DrawFormatStringToHandle(_x + 1160,         _y + Y, GetColor(220, 220, 220), _font, "%s", _header->gameVersion);
}
