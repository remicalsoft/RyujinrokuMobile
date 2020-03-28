#pragma once
#include "Scene.h"
#include <vector>
#include "ISceneChangedListener.h"
#include "ScenePrmBase.h"
#include "GameScenePrm.h"
#include <string>

const static int W = 2186;
const static int H = 3095;

class Pos{
public:
	float x, y;
	float scale;
	Pos() {}
	Pos(float x, float y, float scale) {
		this->x = ((float)x-(W/2)) / (W/2);
		this->y = ((float)y-(H/2)) / (H/2);
		this->scale = scale;
	}
	static Pos createInitPos() {
		return Pos(W,-H/4,0.5);
	}
};

class BaseComicScene : public Scene {

    void playVoice();

protected:
	eStage _stage;
	eLevel _level;
	std::vector<Pos> _posList;
	std::vector<std::vector<Pos>> _list;
	std::vector<char*> _fileList;
	std::vector<int> _imageList;
	Pos _pos, _prePos;
	int _coma, _page, _totalComa;
	int _image, _imgBack;
	int _color;
	int _counter;
	bool _isFromMenu, _gotoEndroll;
	int _font;
    std::string _voiceFilePathPrefix;

	virtual void setPrm() = 0;
    virtual void setVoiceFilePathPrefix() = 0;
	void goNextScene();
	void readFileName(char* mjName);

public:
	BaseComicScene(ISceneChangedListener* impl, ScenePrmBase* prm);
	virtual ~BaseComicScene();
	bool initialize() override;
	void finalize() override;
	bool update() override;
	void draw() override;
};

