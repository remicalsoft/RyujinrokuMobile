#pragma once
#include "BaseComicScene.h"

class ExEdScene : public BaseComicScene {
protected:
	void setPrm();
    void setVoiceFilePathPrefix() override {}

public:
	ExEdScene(ISceneChangedListener* impl, ScenePrmBase* prm);
};

