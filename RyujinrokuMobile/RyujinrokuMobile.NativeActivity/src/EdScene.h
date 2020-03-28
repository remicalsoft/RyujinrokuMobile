#pragma once
#include "BaseComicScene.h"

//const static int W = 2300;
//const static int H = 3400;

class EdScene : public BaseComicScene {
protected:
	void setPrm();
    void setVoiceFilePathPrefix() override;

public:
	EdScene(ISceneChangedListener* impl, ScenePrmBase* prm);
};

