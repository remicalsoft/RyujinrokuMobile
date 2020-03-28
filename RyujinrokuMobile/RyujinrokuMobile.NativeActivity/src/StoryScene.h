#pragma once
#include "Scene.h"
#include"ScenePrmBase.h"
#include <vector>
#include <string>

enum eStory {
	eStoryWorld,
	eStoryRoyokei,
	eStoryBreed,
	eStoryAisha,
	eStoryMayor,
	eStory1,
	eStory2,
	eStory3,
	eStory4,
	eStory5,
	eStoryEx,
	eStoryPh,
	eStoryNone,
};

class StoryScene : public Scene
{
	eStory _storyType;
	int _imgBack, _imgArrow, _imgChar;
	int _font;
	int _color;
	int _scrollY;
	int _counter;
	std::vector<std::string*> _txt;

public:
	StoryScene(ISceneChangedListener * impl, ScenePrmBase *prm);
	~StoryScene();
	bool update() override;
	void draw() override;
};

