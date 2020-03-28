#include "EdScene.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include "SceneStoryParam.h"

using namespace std;

const static int CEN = W / 2;
const static int SPD = 40;

EdScene::EdScene(ISceneChangedListener* impl, ScenePrmBase* prm) : BaseComicScene(impl, prm) {
}

void EdScene::setPrm() {
	{//00.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,  791, 0.8));
		posList.push_back(Pos(CEN, 1550, 0.8));
		posList.push_back(Pos(1376,2288, 0.9));
		posList.push_back(Pos(419, 2390, 1.0));
		_list.push_back(posList);
	}
	{//01.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1604, 758, 1.0));
		posList.push_back(Pos(749,  809, 1.0));
		posList.push_back(Pos(CEN, 1511, 0.8));
		posList.push_back(Pos(CEN, 2084, 0.8));
		posList.push_back(Pos(CEN, 2678, 0.8));
		_list.push_back(posList);
	}
	{//02.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 905, 0.7));
		posList.push_back(Pos(CEN,1727, 0.8));
		posList.push_back(Pos(CEN,2585, 0.7));
		_list.push_back(posList);
	}
	{//03.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN,  455, 0.7));
		posList.push_back(Pos(CEN, 1184, 0.8));
		posList.push_back(Pos(1706,1847, 1.0));
		posList.push_back(Pos(1091,1895, 1.2));
		posList.push_back(Pos(383, 1950, 1.3));
		posList.push_back(Pos(CEN, 2675, 0.8));
		_list.push_back(posList);
	}
	{//04.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 647, 0.8));
		posList.push_back(Pos(CEN,1529, 0.7));
		posList.push_back(Pos(CEN,2402, 0.8));
		_list.push_back(posList);
	}
	{//05.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1508, 806, 0.9));
		posList.push_back(Pos( 770, 839, 0.9));
		posList.push_back(Pos(1622,1493, 1.2));
		posList.push_back(Pos( 869,1499, 1.1));
		posList.push_back(Pos(1505,2222, 0.8));
		posList.push_back(Pos( 746,2258, 0.8));
		_list.push_back(posList);
	}
	{//06.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1442, 791, 0.9));
		posList.push_back(Pos( 572, 830, 0.9));
		posList.push_back(Pos(1127,1757, 0.8));
		posList.push_back(Pos(1466,2456, 1.3));
		posList.push_back(Pos( 569,2594, 1.0));
		_list.push_back(posList);
	}
	{//07.jpg
		vector<Pos> posList;
		posList.push_back(Pos(1643,893, 0.8));
		posList.push_back(Pos(887, 953, 0.8));
		posList.push_back(Pos(CEN,1700, 0.8));
		posList.push_back(Pos(CEN,2360, 0.8));
		_list.push_back(posList);
	}
	{//08.jpg
		vector<Pos> posList;
		posList.push_back(Pos( CEN, 875, 0.7));
		posList.push_back(Pos( CEN,1688, 0.85));
		posList.push_back(Pos(1583,2360, 0.95));
		posList.push_back(Pos( 827,2363, 0.95));
		_list.push_back(posList);
	}
	{//09.jpg
		vector<Pos> posList;
		posList.push_back(Pos(CEN, 821, 0.75));
		posList.push_back(Pos(CEN,1631, 0.8));
		posList.push_back(Pos(CEN,2048, 1.0));
		posList.push_back(Pos(CEN,2339, 1.3));
		posList.push_back(Pos(CEN,2582, 1.1));
		_list.push_back(posList);
	}

	readFileName("01.ed");
}

void EdScene::setVoiceFilePathPrefix(){
    _voiceFilePathPrefix = string("dat/voice/commic/01/");
}
