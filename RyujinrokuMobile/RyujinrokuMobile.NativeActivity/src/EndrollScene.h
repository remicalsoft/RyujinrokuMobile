#pragma once

#include "Scene.h"
#include <list>
#include "NameBullet.h"
#include <memory>
#include "EndrollImage.h"

class EndrollScene :
	public Scene
{
	int _counter;
	int _intervalCounter;
	int _font;
	int _endrollImageN;
	bool _isNameShowing;
	int _staffID;
	int _nameN;
	int _bgm;
	bool _isRegisterable;
	EndrollImage *_endrollImage;

	std::list<std::shared_ptr<NameBullet>> _list;

public:
	EndrollScene(ISceneChangedListener *impl, ScenePrmBase * prm);
	~EndrollScene();
	bool update() override;
	void draw() override;
};

