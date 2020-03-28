#include "FadableScene.h"
#include "ShoIntroScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "SE.h"

const static int TIME = 60;

int ShoIntroScene::getFadeTime()
{
	return TIME;
}

ShoIntroScene::ShoIntroScene(ISceneChangedListener * impl, ScenePrmBase* prm) : FadableScene(impl)
{
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_img[0] = LoadGraph("dat/image/menu/shoIntro00.png");
	_img[1] = LoadGraph("dat/image/menu/shoIntro01.png");
	_selectID = 0;
}

ShoIntroScene::~ShoIntroScene()
{
	DeleteGraph(_imgBack);
	DeleteGraph(_img[0]);
	DeleteGraph(_img[1]);
}

bool ShoIntroScene::update()
{
	if (isAvailable()) {
		if (Pad::getIns()->get(ePad::shot) == 1) {
			switch (_selectID) {
			case 0:
				_selectID++;
				SE::getIns()->setPlay(eSE_page);
				break;
			case 1:
				startFadeout();
				break;
			}
		}
		if (Pad::getIns()->get(ePad::bom) == 1) {
			startFadeout();
		}
	}
	if (!FadableScene::update()) {
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
		return false;
	}
	return true;
}

void ShoIntroScene::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _brightness);
	DrawGraph(0, 0, _imgBack, FALSE);
	DrawGraph(0, 0, _img[_selectID], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

