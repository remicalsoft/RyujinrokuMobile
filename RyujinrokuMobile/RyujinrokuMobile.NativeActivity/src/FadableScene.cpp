#include "FadableScene.h"

FadableScene::FadableScene(ISceneChangedListener* impl) : Scene(impl)
{
	_implSceneChanged = impl;
	_isFadein = true;
	_isFadeout = false;
	_fadeCounter = 0;
	_brightness = 0;
}

FadableScene::~FadableScene()
{
}

bool FadableScene::initialize()
{
	FADE_TIME = getFadeTime();
	return true;
}

bool FadableScene::update()
{
	if (_isFadein || _isFadeout) {
		_fadeCounter++;
		if (_isFadein) {
			_brightness = 255 * _fadeCounter / FADE_TIME;
		}
		if (_isFadeout) {
			_brightness = 255 - 255 * _fadeCounter / FADE_TIME;
		}
		if (_fadeCounter == FADE_TIME) {
			if (_isFadeout) {
				return false;
			}
			_fadeCounter = 0;
			_isFadein = false;
			_isFadeout = false;
		}
	}
	return true;
}

void FadableScene::draw()
{
}

bool FadableScene::isAvailable()
{
	return !(_isFadein || _isFadeout);
}

void FadableScene::startFadein()
{
	_isFadein = true;
	_isFadeout = false;
	_fadeCounter = 0;
}

void FadableScene::startFadeout()
{
	_isFadein = false;
	_isFadeout = true;
	_fadeCounter = 0;
}