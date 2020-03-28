#include "ExEdScene.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include "SceneStoryParam.h"

using namespace std;

const static int CEN = W / 2;
const static int SPD = 40;

ExEdScene::ExEdScene(ISceneChangedListener* impl, ScenePrmBase* prm) : BaseComicScene(impl, prm) {
}

void ExEdScene::setPrm() {
	{//00.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 832, 0.82));
		posList.push_back(Pos(CEN,1580, 0.82));
		posList.push_back(Pos(CEN,2130, 0.82));
		posList.push_back(Pos(CEN,2713, 0.82));
		_list.push_back(posList);
	}
	{//01.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 614, 0.82));
		posList.push_back(Pos(1479, 1147, 1.2));
		posList.push_back(Pos(706, 1158, 1.2));
		posList.push_back(Pos(CEN, 1838, 0.82));
		posList.push_back(Pos(CEN, 2652, 0.8));
		_list.push_back(posList);
	}
	{//02.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,867,0.6));
		posList.push_back(Pos(CEN,1720,0.82));
		posList.push_back(Pos(1350, 2362, 1.1));
		posList.push_back(Pos(425, 2513, 0.8));
		_list.push_back(posList);
	}
	{//03.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,838,0.8));
		posList.push_back(Pos(CEN,1573,0.82));
		posList.push_back(Pos(1525,2382,0.8));
		posList.push_back(Pos(657,2370,0.75));
		_list.push_back(posList);
	}
	{//04.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1555,801, 1.0));
		posList.push_back(Pos(828,796, 1.0));
		posList.push_back(Pos(CEN,1576, 0.82));
		posList.push_back(Pos(1297,2278, 0.75));
		posList.push_back(Pos(506,2310, 1.0));
		_list.push_back(posList);
	}
	{//05.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 491, 1.4));
		posList.push_back(Pos(1621,1177,0.7));
		posList.push_back(Pos(753,1177,0.7));
		posList.push_back(Pos(CEN,1914,0.82));
		posList.push_back(Pos(CEN,2535,0.75));
		_list.push_back(posList);
	}
	{//06.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1462,786,1.0));
		posList.push_back(Pos(709,794,1.0));
		posList.push_back(Pos(CEN,1480,0.82));
		posList.push_back(Pos(CEN,2220,0.75));
		_list.push_back(posList);
	}
	{//07.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1491,752,0.9));
		posList.push_back(Pos(734,724,1.0));
		posList.push_back(Pos(CEN,1888, 0.5));
		_list.push_back(posList);
	}
	{//08.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,759,0.8));
		posList.push_back(Pos(CEN,1335,0.8));
		posList.push_back(Pos(1558,2196,0.75));
		posList.push_back(Pos(789,2206,0.75));
		_list.push_back(posList);
	}
	{//09.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,1531,0.4));
		_list.push_back(posList);
	}
	readFileName("03.exed");
}
