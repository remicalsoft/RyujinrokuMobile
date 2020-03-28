#pragma once
#include "ScenePrmBase.h"
#include "StoryScene.h"

class SceneStoryParam : public ScenePrmBase
{
public:
	eStory  story;
	bool isFromMenu;
	bool gotoEndroll;
	SceneStoryParam();
	~SceneStoryParam();
};

