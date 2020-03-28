#pragma once
#include "BaseComicScene.h"

//const static int W = 2300;
//const static int H = 3400;

class OpScene : public BaseComicScene {
protected:
	void setPrm() override;
    void setVoiceFilePathPrefix() override;

public:
	OpScene(ISceneChangedListener* impl, ScenePrmBase* prm);
};

