#pragma once

#include "FadableScene.h"
#include "ISceneChangedListener.h"
#include <vector>
#include "ReplayCell.h"

class ISceneChangedListener;

class ReplayScene : public FadableScene
{

	int _img;
	int _imgCell, _imgTitleCell, _imgCellSelected;
	int _counter;
	int _imgW, _imgH;
	int _font;
	int _selectID;
	int _seetID;
	std::vector<ReplayCell*> _list;

protected:
	int getFadeTime() override;

public:
	ReplayScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~ReplayScene();
	void initializeCell();
	void updateCell();
	bool update() override;
	void draw() override;

};

