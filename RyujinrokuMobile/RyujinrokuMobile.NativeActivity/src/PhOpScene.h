#pragma once
#include "BaseComicScene.h"
class PhOpScene : public BaseComicScene {
protected:
	void setPrm();
    void setVoiceFilePathPrefix() override {}

public:
	PhOpScene(ISceneChangedListener* impl, ScenePrmBase* prm);
};