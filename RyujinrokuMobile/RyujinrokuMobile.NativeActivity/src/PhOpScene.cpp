#include "PhOpScene.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include "SceneStoryParam.h"

using namespace std;

const static int CEN = W / 2;
const static int SPD = 40;

PhOpScene::PhOpScene(ISceneChangedListener* impl, ScenePrmBase* prm) : BaseComicScene(impl, prm) {
}

void PhOpScene::setPrm() {
	{//00.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 632, 0.82));
		posList.push_back(Pos(CEN, 1070, 0.82));
		posList.push_back(Pos(CEN, 1436, 0.82));
		posList.push_back(Pos(CEN, 2256, 0.6));
		_list.push_back(posList);
	}
	{//01.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 719, 0.77));
		posList.push_back(Pos(1616, 1562, 1.3));
		posList.push_back(Pos(845, 1571, 1.1));
		posList.push_back(Pos(CEN, 2474, 0.65));
		_list.push_back(posList);
	}
	{//02.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1412, 779, 0.9));
		posList.push_back(Pos(656, 788, 1.1));
		posList.push_back(Pos(CEN, 1502, 0.82));
		posList.push_back(Pos(CEN, 2438, 0.6));
		_list.push_back(posList);
	}
	{//03.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,734, 0.82));
		posList.push_back(Pos(CEN,1364, 0.82));
		posList.push_back(Pos(1559, 2255, 0.9));
		posList.push_back(Pos(797,2252, 0.9));
		_list.push_back(posList);
	}
	{//04.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 818, 0.82));
		posList.push_back(Pos(CEN, 1406, 0.82));
		posList.push_back(Pos(1346, 1805, 1.0));
		posList.push_back(Pos(1595,2357, 1.3));
		posList.push_back(Pos(845,2405, 1.1));
		_list.push_back(posList);
	}
	{//05.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 773, 0.70));
//		posList.push_back(Pos(440, 840, 1.4));
		posList.push_back(Pos(1730, 2081, 0.50));
		posList.push_back(Pos(560,2217, 0.60));
		_list.push_back(posList);
	}
	{//06.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1460,755,0.8));
		posList.push_back(Pos(707, 848, 0.9));
		posList.push_back(Pos(CEN, 1616, 0.82));
		posList.push_back(Pos(1499,2318,1.2));
		posList.push_back(Pos(701,2360,1.2));
		_list.push_back(posList);
	}
	{//07.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,950,0.82));
		posList.push_back(Pos(CEN,1706,0.82));
		posList.push_back(Pos(CEN,2372,0.82));
		_list.push_back(posList);
	}
	{//08.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,695, 0.82));
		posList.push_back(Pos(CEN,1223, 0.82));
		posList.push_back(Pos(CEN,2177, 0.62));
		_list.push_back(posList);
	}
	{//09.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 773, 0.82));
		posList.push_back(Pos(CEN,1703, 0.82));
		posList.push_back(Pos(CEN,2447, 0.82));
		_list.push_back(posList);
	}
	{//10.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1394,923, 0.8));
		posList.push_back(Pos(659, 923, 0.8));
		posList.push_back(Pos(CEN, 1802, 0.82));
		posList.push_back(Pos(CEN, 2474, 0.82));
		_list.push_back(posList);
	}
	{//11.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1445,755, 1.2));
		posList.push_back(Pos(716, 755, 1.3));
		posList.push_back(Pos(CEN, 1325, 0.82));
		posList.push_back(Pos(CEN, 2100, 0.82));
		_list.push_back(posList);
	}
	{//12.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 583, 0.82));
		posList.push_back(Pos(CEN,1735, 0.5));
		_list.push_back(posList);
	}
	readFileName("04.phop");
}
