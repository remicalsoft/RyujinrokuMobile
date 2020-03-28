#pragma once

#include "Scene.h"
#include "ISceneChangedListener.h"

class ISceneChangedListener;

class FadableScene : public Scene
{

protected:
	int FADE_TIME;
	bool _isFadein, _isFadeout;
	int _fadeCounter;
	int _brightness;
	ISceneChangedListener* _implSceneChanged;

	bool isAvailable();
	void startFadein();
	void startFadeout();

	virtual int getFadeTime() = 0;

public:
	FadableScene(ISceneChangedListener *impl);
	virtual ~FadableScene();
	virtual bool initialize() override;
	virtual bool update() override;
	virtual void draw() override;

};

