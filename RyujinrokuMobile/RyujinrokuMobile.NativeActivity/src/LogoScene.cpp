#include "FadableScene.h"
#include "LogoScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"

const static int TIME = 60;
const static int MAX_COUNT = 240;

int LogoScene::getFadeTime()
{
	return TIME;
}

LogoScene::LogoScene(ISceneChangedListener * impl, ScenePrmBase* prm) : FadableScene(impl)
{
	_img = LoadGraph("dat/image/logo/logo.png");
	GetGraphSize(_img, &_imgW, &_imgH);
	_counter = 0;
}

LogoScene::~LogoScene()
{
	DeleteGraph(_img);
}

bool LogoScene::update()
{
	_counter++;
	if (isAvailable()) {
		if (_counter == MAX_COUNT) {
			startFadeout();
		}
		else if (Pad::getIns()->get(ePad::shot) == 1) {
			startFadeout();
		}
	}
	if (!FadableScene::update()) {
		_implSceneChanged->onSceneChanged(eScene::Menu, false, nullptr);
		return false;
	}
	return true;
}

void LogoScene::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _brightness);
	DrawGraph((WIN_W - _imgW) / 2, (WIN_H - _imgH) / 2, _img, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

