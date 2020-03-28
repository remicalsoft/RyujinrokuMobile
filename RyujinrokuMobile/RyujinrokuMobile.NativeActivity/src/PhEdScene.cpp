#include "PhEdScene.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include "SceneStoryParam.h"

using namespace std;

const static int CEN = W / 2;
const static int SPD = 40;

PhEdScene::PhEdScene(ISceneChangedListener* impl, ScenePrmBase* prm) : BaseComicScene(impl, prm) {
}

void PhEdScene::setPrm() {
	{//00.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,658, 0.7));
		posList.push_back(Pos(1523,1503, 1.2));
		posList.push_back(Pos(749,1427, 1.1));
		posList.push_back(Pos(CEN, 2085, 0.75));
		posList.push_back(Pos(CEN,2664, 0.68));
		_list.push_back(posList);
	}
	{//01.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1566,939, 0.8));
		posList.push_back(Pos(806,834, 0.9));
		posList.push_back(Pos(CEN,1531, 0.82));
		posList.push_back(Pos(CEN,2463, 0.6));
		_list.push_back(posList);
	}
	{//02.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1392,715, 0.6));
		posList.push_back(Pos(578,665, 0.7));
		posList.push_back(Pos(CEN,2169, 0.5));
		_list.push_back(posList);
	}
	{//03.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 986, 0.5));
		posList.push_back(Pos(CEN, 2050, 0.82));
		posList.push_back(Pos(CEN, 2594, 0.82));
		_list.push_back(posList);
	}
	{//04.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1527,845, 0.85));
		posList.push_back(Pos(678,809, 0.9));
		posList.push_back(Pos(CEN,1703, 0.68));
		posList.push_back(Pos(1511, 2532, 1.0));
		posList.push_back(Pos(510,2492, 1.1));
		_list.push_back(posList);
	}
	{//05.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 696, 0.82));
		posList.push_back(Pos(1558,1378, 0.9));
		posList.push_back(Pos(808,1389, 0.9));
		posList.push_back(Pos(CEN,2256, 0.78));
		_list.push_back(posList);
	}
	{//06.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,717, 0.8));
		posList.push_back(Pos(CEN,1700, 0.82));
		posList.push_back(Pos(1472,2210, 0.9));
		posList.push_back(Pos(647,2310, 1.0));
		_list.push_back(posList);
	}
	{//07.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 1100,  0.65));
		posList.push_back(Pos(CEN, 2150, 0.80));
		_list.push_back(posList);
	}
	{//08.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 875, 0.8));
		posList.push_back(Pos(1655, 1841, 0.75));
		posList.push_back(Pos(947, 1841, 0.75));
		posList.push_back(Pos(CEN, 2642, 0.82));
		_list.push_back(posList);
	}
	{//09.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 509, 0.82));
		posList.push_back(Pos(CEN, 1103, 0.82));
		posList.push_back(Pos(CEN, 1634, 0.82));
		posList.push_back(Pos(CEN, 2312, 0.82));
		_list.push_back(posList);
	}
	{//10.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 746, 0.82));
		posList.push_back(Pos(1520,1643 , 0.82));
		posList.push_back(Pos(743,1634 , 0.82));
		posList.push_back(Pos(CEN, 2501, 0.82));
		_list.push_back(posList);
	}
	{//11.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1340,851 , 0.9));
		posList.push_back(Pos(596,842 , 0.9));
		posList.push_back(Pos(1526,1538 , 1.2));
		posList.push_back(Pos(773, 1547, 1.1));
		posList.push_back(Pos(1340, 2252, 0.9));
		posList.push_back(Pos(536,2300 , 1.0));
		_list.push_back(posList);
	}
	{//12.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1415, 833, 1.0));
		posList.push_back(Pos(650,845 , 1.0));
		posList.push_back(Pos(CEN, 1607, 0.82));
		posList.push_back(Pos(1610, 2252, 1.05));
		posList.push_back(Pos(794,2288 , 1.0));
		_list.push_back(posList);
	}
	{//13.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 812, 0.82));
		posList.push_back(Pos(1493, 1301, 1.2));
		posList.push_back(Pos(1550,1814 , 1.2));
		posList.push_back(Pos(785, 1649, 1.0));
		posList.push_back(Pos(CEN, 2590, 0.825));
		_list.push_back(posList);
	}
	readFileName("05.phed");
}
