#include "StoryScene.h"
#include "SceneStoryParam.h"
#include <string>
#include <DxLib.h>
#include "Define.h"
#include "Pad.h"
#include "SE.h"

const static int WINDOW_X = 24;
const static int WINDOW_Y = 66;
const static int WINDOW_W = 887;
const static int WINDOW_H = 820;
const static int FONT_SIZE = 18;
const static int LINE_SIZE = 25;

char *fnamePrm[] = {
	"world",
	"royokei",
	"breed",
	"aisha",
	"mayor",
	"1",
	"2",
	"3",
	"4",
	"5",
	"ex",
	"ph",
};

using namespace std;

StoryScene::StoryScene(ISceneChangedListener * impl, ScenePrmBase *prm) : Scene(impl)
{
	SceneStoryParam* p = nullptr;
	p = dynamic_cast<SceneStoryParam*>(prm);
	_storyType = p->story;
	{
		char fname[256];
		sprintf(fname, "dat/txt/story/%s.txt", fnamePrm[_storyType]);
		int file = FileRead_open(fname);
		char txt[512];
		while (1) {
			if (FileRead_gets(txt, 512, file) == -1) {
				break;
			}
			string* str = new string(txt);
			_txt.push_back(str);
		}
	}
	{
		char fname[256];
		sprintf(fname, "dat/image/story/%s.png", fnamePrm[_storyType]);
		_imgChar = LoadGraph(fname);
	}
	_imgBack = LoadGraph("dat/image/menu/back_dark_board.png");
	_imgArrow = LoadGraph("dat/image/story/arrow.png");
	_font = CreateFontToHandle(FONT, FONT_SIZE, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	_color = GetColor(200, 200, 200);
	_scrollY = 0;
	_counter = 0;
}

StoryScene::~StoryScene()
{
	for (int i = 0; i < _txt.size(); i++) {
		delete _txt[i];
	}
	DeleteGraph(_imgBack);
	DeleteGraph(_imgArrow);
	DeleteGraph(_imgChar);
	DeleteFontToHandle(_font);
}

bool StoryScene::update(){
	_counter++;
	if (Pad::getIns()->get(ePad::bom) == 1) {
		SE::getIns()->setPlay(eSE::eSE_cancel);
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
	}
	if (WINDOW_H < _txt.size()*LINE_SIZE) {
		if (Pad::getIns()->get(ePad::up) >= 1) {
			if (_scrollY > 0) {
				_scrollY-=4;
				if (_scrollY < 0) {
					_scrollY = 0;
				}
			}
		}
		if (Pad::getIns()->get(ePad::down) >= 1) {
			_scrollY+=4;
			int sub = _txt.size()*LINE_SIZE - WINDOW_H;
			if (_scrollY > sub) {
				_scrollY = sub;
			}
		}
	}
	return false;
}

void StoryScene::draw()
{
	bool upable = _scrollY > 0;
	bool downable = false;
	if (WINDOW_H < _txt.size()*LINE_SIZE) {
		downable = true;
		if (_scrollY == _txt.size()*LINE_SIZE - WINDOW_H) {
			downable = false;
		}
	}
	DrawGraph(0,0,_imgBack,FALSE);
	if (upable) {
		DrawRotaGraph(400, 40-((_counter / 3) % 10), 1, 0, _imgArrow, TRUE);
	}
	if (downable) {
		DrawRotaGraph(400, WIN_H-42+((_counter/3)%10), 1, PI, _imgArrow, TRUE);
	}
	SetDrawArea(WINDOW_X, WINDOW_Y, WINDOW_X + WINDOW_W, WINDOW_Y + WINDOW_H);
	for (int i = 0; i < _txt.size(); i++) {
		DrawStringToHandle(WINDOW_X+20, -_scrollY + WINDOW_Y + LINE_SIZE * i, _txt[i]->c_str(), _color, _font);
	}
	SetDrawArea(0, 0, WIN_W, WIN_H);
	DrawGraph(WIN_W-357, WINDOW_Y, _imgChar, TRUE);
}


