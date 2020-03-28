#pragma once
#include "BaseComicScene.h"

//const static int W = 2300;
//const static int H = 3400;

class ExOpScene : public BaseComicScene {
protected:
	void setPrm();
    void setVoiceFilePathPrefix() override;

public:
	ExOpScene(ISceneChangedListener* impl, ScenePrmBase* prm);
};

