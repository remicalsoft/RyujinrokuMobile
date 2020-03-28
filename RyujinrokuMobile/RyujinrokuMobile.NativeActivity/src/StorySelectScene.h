#pragma once
#include "Scene.h"
#include "ScenePrmBase.h"
#include "Explanations.h"

class StorySelectScene : public Scene
{
	int _font;
	int _imgBack;
	int _colorSelected, _colorOther;
	int _selectID;
	int _counter;
	Explanations* _explanation;
    int _debugCommandStatus;

    void updateDebugCommand();

public:
	StorySelectScene(ISceneChangedListener* impl, ScenePrmBase* prm);
	~StorySelectScene();
	bool update() override;
	void draw() override;
};

