#include "ExOpScene.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include "SceneStoryParam.h"

using namespace std;

const static int CEN = W / 2;
const static int SPD = 40;

ExOpScene::ExOpScene(ISceneChangedListener* impl, ScenePrmBase* prm) : BaseComicScene(impl, prm) {
}

void ExOpScene::setPrm() {
	{//00.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,685, 0.82));
		posList.push_back(Pos(CEN,1244, 0.82));
		posList.push_back(Pos(1516,1884, 1.0));
		posList.push_back(Pos(735,1866, 1.0));
		posList.push_back(Pos(CEN,2476, 0.82));
		_list.push_back(posList);
	}
	{//01.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,  712, 0.82));
		posList.push_back(Pos(1369,1337, 1.1));
		posList.push_back(Pos(579, 1316, 1.1));
		posList.push_back(Pos(CEN, 1941, 0.82));
		posList.push_back(Pos(1486,2466, 1.3));
		posList.push_back(Pos(762, 2466, 1.3));
		_list.push_back(posList);
	}
	{//02.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,  739, 0.82));
		posList.push_back(Pos(1447,1361, 1.2));
		posList.push_back(Pos(528, 1361, 1.1));
		posList.push_back(Pos(CEN, 1983, 0.82));
		posList.push_back(Pos(CEN, 2476, 0.82));
		_list.push_back(posList);
	}
	{//03.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,  697, 0.82));
		posList.push_back(Pos(CEN, 1256, 0.82));
		posList.push_back(Pos(CEN, 1703, 0.82));
		posList.push_back(Pos(CEN, 2466, 0.60));
		_list.push_back(posList);
	}

	readFileName("02.exop");
}

void ExOpScene::setVoiceFilePathPrefix() {
    _voiceFilePathPrefix = string("dat/voice/commic/02/");
}
