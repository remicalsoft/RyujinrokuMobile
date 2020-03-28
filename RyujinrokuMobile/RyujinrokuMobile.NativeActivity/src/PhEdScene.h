#pragma once
#include "BaseComicScene.h"
class PhEdScene : public BaseComicScene {
protected:
	void setPrm();
    void setVoiceFilePathPrefix() override {}

public:
	PhEdScene(ISceneChangedListener* impl, ScenePrmBase* prm);
};