#include "OpScene.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include "SceneStoryParam.h"

using namespace std;

const static int CEN = W / 2;
const static int SPD = 40;

OpScene::OpScene(ISceneChangedListener* impl, ScenePrmBase* prm) : BaseComicScene(impl, prm) {
}

void OpScene::setPrm() {
	{//00.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,  610, 0.82));
		posList.push_back(Pos(1424,1112, 1.35));
		posList.push_back(Pos(736, 1112, 1.35));
		posList.push_back(Pos(CEN, 1627, 0.82));
		posList.push_back(Pos(CEN, 2354, 0.82));
		_list.push_back(posList);
	}
	{//01.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 878, 0.85));
		posList.push_back(Pos(CEN,1840, 0.85));
		posList.push_back(Pos(CEN,2519, 0.85));
		_list.push_back(posList);
	}
	{//02.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1362,689,  1.3));
		posList.push_back(Pos(595, 677,  1.3));
		posList.push_back(Pos(CEN, 1245, 0.85));
		posList.push_back(Pos(1516,2104, 0.7));
		posList.push_back(Pos(724, 1849, 1.2));
		posList.push_back(Pos(769, 2427, 1.3));
		_list.push_back(posList);
	}
	{//03.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1424,675, 1.2));
		posList.push_back(Pos(642,642, 1.3));
		posList.push_back(Pos(CEN, 1213, 0.82));
		posList.push_back(Pos(1424,2089, 0.7));
		posList.push_back(Pos(642,1742, 1.3));
		posList.push_back(Pos(662,2318, 1.1));
		_list.push_back(posList);
	}
	{//04.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 1020, 0.65));
		posList.push_back(Pos(CEN, 1829, 0.82));
		posList.push_back(Pos(1421,2400, 1.2));
		posList.push_back(Pos(707, 2407, 1.3));
		_list.push_back(posList);
	}
	{//05.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1337, 853, 0.9));
		posList.push_back(Pos(600, 853, 0.9));
		posList.push_back(Pos(CEN, 1636, 0.82));
		posList.push_back(Pos(1446, 2334, 1.1));
		posList.push_back(Pos(730,2334, 1.1));
		_list.push_back(posList);
	}
	{//06.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1351,830,0.9));
		posList.push_back(Pos(618,830, 0.9));
		posList.push_back(Pos(CEN,1573, 0.82));
		posList.push_back(Pos(1570,2282, 1.0));
		posList.push_back(Pos(875,2261, 1.0));
		_list.push_back(posList);
	}

	readFileName("00.op");
}

void OpScene::setVoiceFilePathPrefix(){
    _voiceFilePathPrefix = string("dat/voice/commic/00/");
}
