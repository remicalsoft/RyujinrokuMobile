#include "Board.h"
#include <DxLib.h>
#include "Define.h"
#include "Image.h"
#include "GameCounter.h"
#include "GameData.h"
#include "SavedData.h"
#include "DebugMode.h"
#include "Utils.h"
#include "vector"
#include "Replayer.h"

using namespace std;

Board::Board()
{
	_font = CreateFontToHandle(FONT, 16, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_counter = 0;
	_icons[eEquipItem_Dress] = LoadGraph("dat/image/icon/dress.png");
	_icons[eEquipItem_Ring] = LoadGraph("dat/image/icon/kyushu0.png");
	_icons[eEquipItem_Ring2] = LoadGraph("dat/image/icon/kyushu1.png");
	_icons[eEquipItem_Hoseki] = LoadGraph("dat/image/icon/border0.png");
	_icons[eEquipItem_Hoseki2] = LoadGraph("dat/image/icon/border1.png");
	_icons[eEquipItem_Jacket] = LoadGraph("dat/image/icon/atari0.png");
	_icons[eEquipItem_Jacket2] = LoadGraph("dat/image/icon/atari1.png");
	_icons[eEquipItem_Pheromone] = LoadGraph("dat/image/icon/enemy0.png");
	_icons[eEquipItem_Pheromone2] = LoadGraph("dat/image/icon/enemy1.png");
	_icons[eEquipItem_Soul] = LoadGraph("dat/image/icon/power0.png");
	_icons[eEquipItem_Soul2] = LoadGraph("dat/image/icon/power1.png");
	_icons[eEquipItem_Bomb] = LoadGraph("dat/image/icon/bomb0.png");
	_icons[eEquipItem_Bomb2] = LoadGraph("dat/image/icon/bomb1.png");
}

Board::~Board()
{
	DeleteFontToHandle(_font);
	for (int i = 0; i < eEquipItem_Num - 1; i++) {
		DeleteGraph(_icons[i]);
	}
}

bool Board::update() {
	_counter++;
	if (!Replayer::getIns()->isReplaying()) {
		int stage = GameData::getIns()->stage;
		int level = GameData::getIns()->level;
		if (eStage1<=stage && stage<=eStage5) {
			stage = eStage1;
		}
		if (SavedData::getIns()->dat.hiScore[level][stage] < GameData::getIns()->score) {
			SavedData::getIns()->dat.hiScore[level][stage] = GameData::getIns()->score;
		}
	}
	return true;
}

void drawNumber(int x, int y, int val) {
	int n = 0;
	int tmp = val;
	while (1) {
		n++;
		tmp /= 10;
		if (tmp == 0) {
			break;
		}
	}
	for (int i = 0; i < n; i++){
		int num = pow(10, n - i - 1);
		DrawGraph(x,y,Image::getIns()->boardNumber[(val/num)%10],TRUE);
		x += 14;
	}
}

const static int ICON_X = 973;
const static int ICON_Y = 900;
const static int ICON_W = 38;
const static int ICON_H = 38;

void Board::draw() {
	DrawGraph(OUT_W, 0, Image::getIns()->board, TRUE);
	int cnt = GameCounter::getIns()->get();
	int img = Image::getIns()->player[0];
	int x = OUT_W + 20+7;
	int y = WIN_H - 32 - (WIN_H - 64.f) / (float)_endCount*cnt;
	DrawRotaGraph(x, y, 0.54, 0, img, TRUE);

	int stage = GameData::getIns()->stage;
	int level = GameData::getIns()->level;
	if (eStage1 <= stage && stage <= eStage5) {
		stage = eStage1;
	}
	drawNumber(OUT_W + 210,  67, SavedData::getIns()->dat.hiScore[level][stage]);
	drawNumber(OUT_W + 210, 110, GameData::getIns()->score);

	{
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 0, 0.6, +PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Bomb][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 0, 0.3, -PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Bomb][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 0, 0.6, 0, Image::getIns()->item[eItem_Bomb][0], TRUE);
	}
	DrawGraph(OUT_W + 100, 195 + 46 * 0, Image::getIns()->boardFont[1], TRUE);
	drawNumber(OUT_W + 235, 198 + 46 * 0, GameData::getIns()->bomb/ BOMB_PARTS_N);
	DrawFormatStringToHandle(OUT_W + 255, 204 + 46 * 0, GetColor(255, 255, 255), _font, "(%d/%d)", GameData::getIns()->bomb % BOMB_PARTS_N, BOMB_PARTS_N);
	{
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 1, 0.6, +PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Power][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 1, 0.3, -PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Power][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 1, 0.6, 0, Image::getIns()->item[eItem_Power][0], TRUE);
	}
	DrawGraph(OUT_W + 100, 195 + 46 * 1, Image::getIns()->boardFont[0], TRUE);
	drawNumber(OUT_W + 235, 198 + 46 * 1, GameData::getIns()->power);
	{
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 2, 0.6, +PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Score][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 2, 0.3, -PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Score][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 2, 0.6, 0, Image::getIns()->item[eItem_Score][0], TRUE);
	}
	DrawGraph(OUT_W + 100, 195 + 46 * 2, Image::getIns()->boardFont[2], TRUE);
	drawNumber(OUT_W + 235, 198 + 46 * 2, GameData::getIns()->point);
	{
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 3, 0.6, +PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Money][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 3, 0.3, -PI * 2 / 360 * _counter, Image::getIns()->item[eItem_Money][1], TRUE);
		DrawRotaGraphF(OUT_W + 75, 212 + 46 * 3, 0.6, 0, Image::getIns()->item[eItem_Money][0], TRUE);
	}
	DrawGraph(OUT_W + 100, 195 + 46 * 3, Image::getIns()->boardFont[4], TRUE);
	drawNumber(OUT_W + 235, 198 + 46 * 3, GameData::getIns()->getMoney());

	DrawGraph(OUT_W + 100, 195 + 46 * 4, Image::getIns()->boardFont[3], TRUE);
	drawNumber(OUT_W + 235, 198 + 46 * 4, GameData::getIns()->graze);

//	DrawGraph(WIN_W - 170, WIN_H - 35, Image::getIns()->level[GameData::getIns()->level], TRUE);
//	DrawGraph(WIN_W - 280, -5, Image::getIns()->level[GameData::getIns()->level], TRUE);

	/*
	if (DebugMode::getIns()->isON == true)	//スコアの内訳表示
	{
		for (int i = 0; i < GameData::eScoreType_Num; i++)
		{
			DrawFormatStringToHandle(OUT_W + 45, 450 + 20 * i, GetColor(255, 255, 255), _font, "%s:", GameData::getIns()->scoreStr[i].c_str());
			DrawFormatStringToHandle(OUT_W + 255, 450 + 20 * i, GetColor(255, 255, 255), _font, "%d", GameData::getIns()->scoreBreakdown[i]);
		}
	}
	*/

	{//レベル・章
		DrawGraph(OUT_W + 140, 0, Image::getIns()->level[GameData::getIns()->level], TRUE);
		DrawGraph(OUT_W + 70, 0, Image::getIns()->stageSho[GameData::getIns()->stage], TRUE);
	}
	{//バージョン表記
		DrawFormatStringToHandle(OUT_W+290, OUT_H-20, GetColor(255, 255, 255), _font, "v%s", Utils::getShortVersionString().c_str());
	}
	{//アイテムゲットボーダーライン
		int y = GameData::getIns()->getItemGetBorderLineH();
		DrawGraph(0,y,Image::getIns()->itemGetBorderLine,TRUE);
	}
	{//装備アイコン
		drawIcon();
	}
	int color = GetColor(0,64,128);
	DrawLine(IN_X,		IN_Y,     IN_X+IN_W,IN_Y,      color);
	DrawLine(IN_X,		IN_Y,     IN_X,     IN_Y+IN_H, color);
	DrawLine(IN_X+IN_W, IN_Y,     IN_X+IN_W,IN_Y+IN_H, color);
	DrawLine(IN_X,      IN_Y+IN_H,IN_X+IN_W,IN_Y+IN_H, color);
}

void Board::drawIcon()
{
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Dress]) {
		DrawGraph(ICON_X, ICON_Y, _icons[eEquipItem_Dress], TRUE);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawGraph(ICON_X, ICON_Y, _icons[eEquipItem_Dress], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Ring] && SavedData::getIns()->dat.isEquiped[eEquipItem_Ring2]) {
		DrawGraph(ICON_X+ICON_W*1, ICON_Y, _icons[eEquipItem_Ring2], TRUE);
	}
	else if (SavedData::getIns()->dat.isEquiped[eEquipItem_Ring] || SavedData::getIns()->dat.isEquiped[eEquipItem_Ring2]) {
		DrawGraph(ICON_X + ICON_W * 1, ICON_Y, _icons[eEquipItem_Ring], TRUE);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawGraph(ICON_X + ICON_W * 1, ICON_Y, _icons[eEquipItem_Ring], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Hoseki] && SavedData::getIns()->dat.isEquiped[eEquipItem_Hoseki2]) {
		DrawGraph(ICON_X + ICON_W * 2, ICON_Y, _icons[eEquipItem_Hoseki2], TRUE);
	}
	else if (SavedData::getIns()->dat.isEquiped[eEquipItem_Hoseki] || SavedData::getIns()->dat.isEquiped[eEquipItem_Hoseki2]) {
		DrawGraph(ICON_X + ICON_W * 2, ICON_Y, _icons[eEquipItem_Hoseki], TRUE);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawGraph(ICON_X + ICON_W * 2, ICON_Y, _icons[eEquipItem_Hoseki], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Jacket] && SavedData::getIns()->dat.isEquiped[eEquipItem_Jacket2]) {
		DrawGraph(ICON_X + ICON_W * 3, ICON_Y, _icons[eEquipItem_Jacket2], TRUE);
	}
	else if (SavedData::getIns()->dat.isEquiped[eEquipItem_Jacket] || SavedData::getIns()->dat.isEquiped[eEquipItem_Jacket2]) {
		DrawGraph(ICON_X + ICON_W * 3, ICON_Y, _icons[eEquipItem_Jacket], TRUE);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawGraph(ICON_X + ICON_W * 3, ICON_Y, _icons[eEquipItem_Jacket], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone] && SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone2]) {
		DrawGraph(ICON_X + ICON_W * 4, ICON_Y, _icons[eEquipItem_Pheromone2], TRUE);
	}
	else if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone] || SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone2]) {
		DrawGraph(ICON_X + ICON_W * 4, ICON_Y, _icons[eEquipItem_Pheromone], TRUE);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawGraph(ICON_X + ICON_W * 4, ICON_Y, _icons[eEquipItem_Pheromone], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Soul] && SavedData::getIns()->dat.isEquiped[eEquipItem_Soul2]) {
		DrawGraph(ICON_X + ICON_W * 5, ICON_Y, _icons[eEquipItem_Soul2], TRUE);
	}
	else if (SavedData::getIns()->dat.isEquiped[eEquipItem_Soul] || SavedData::getIns()->dat.isEquiped[eEquipItem_Soul2]) {
		DrawGraph(ICON_X + ICON_W * 5, ICON_Y, _icons[eEquipItem_Soul], TRUE);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawGraph(ICON_X + ICON_W * 5, ICON_Y, _icons[eEquipItem_Soul], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb] && SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb2]) {
		DrawGraph(ICON_X + ICON_W * 6, ICON_Y, _icons[eEquipItem_Bomb2], TRUE);
	}
	else if (SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb] || SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb2]) {
		DrawGraph(ICON_X + ICON_W * 6, ICON_Y, _icons[eEquipItem_Bomb], TRUE);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawGraph(ICON_X + ICON_W * 6, ICON_Y, _icons[eEquipItem_Bomb], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}
