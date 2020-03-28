#include "FadableScene.h"
#include "ContinueScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"

const static int TIME = 180;
const static int MAX_COUNT = 240;

int ContinueScene::getFadeTime()
{
	return TIME;
}

ContinueScene::ContinueScene(ISceneChangedListener * impl, ScenePrmBase* prm) : FadableScene(impl)
{
	_img = LoadGraph("dat/image/else/continue.png");
	GetGraphSize(_img, &_imgW, &_imgH);
	_counter = 0;
}

ContinueScene::~ContinueScene()
{
	DeleteGraph(_img);
}

bool ContinueScene::update()
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

void ContinueScene::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _brightness);
	DrawGraph((WIN_W - _imgW)-20, (WIN_H - _imgH)-20, _img, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

