#include "StoryPreGameScene.h"
#include <DxLib.h>
#include <string>
#include "Define.h"
#include "Pad.h"
#include <string.h>
#include "SE.h"

using namespace std;

static char* txtDat[] = {
	"この世は「瀧源郷(ろうげんきょう)」と呼ばれており",				//01
	"人間界と妖人界が存在する。",									//02
	"瀧源郷の内、妖人界はこの世の大きさの8割を占めており",			//03
	"人間界は「村」という単位で点在している。",						//04
	"村は各々で自給自足しており、村間の疎通はほとんどない",			//05
	"アイシャが住んでいる「庵村(いおりむら)」は",					//06
	"瀧源郷に存在する多くの村の一つである。",						//07
	"人間界と妖人界は交わらないように生きてきたが意思疎通は可能",	//08
	"しかし人を襲う妖人も存在するため",								//09
	"人間はめったなことでは妖人に関わろうとしない",					//10
	"元々瀧源郷に「夜」という概念は存在しなかった",					//11
	"日が沈まない、常に昼である世界だった",							//12
	"だが妖人界が1日の半分の光を消費して生存するようになった為",	//13
	"光のある「昼」と光のない「夜」が誕生した",						//14
	"特に光を消費するのは妖人界の中でもその王である龍族である",		//15
	"龍族は光を食すことで様々な副次的作用を妖人に引き起こす",		//16
	"その副次的作用で妖人界は保たれており",							//17
	"妖人界の王である龍族無しに妖人は生存することができない",		//18
	"そのため妖人は王である龍族に仕える",							//19
	"昼の光を使って人間は生き",										//20
	"夜の分の光を龍族が食らい夜となり、その作用で妖人が活動する",	//21
	"こうして昼と夜の均衡、そして人間界と妖人界の均衡が保たれていた",//22
	"しかし1ヶ月前、妖人界に異変が起こり",							//23
	"その影響で村に朝がおとずれなくなってしまった",					//24
	"人間界には極まれに魔術を使う魔術師が生まれる",					//25
	"アイシャはその村唯一の魔術師として生まれ、光の魔術を扱う",		//26
	"朝がおとずれなくなってしまった庵村の光を",						//27
	"アイシャは自分の光の魔術を使って補った",						//28
	"しかし庵村全体を照らす程の光の魔術を使うには大きな体力消耗が伴った",//29
	"このままではいられない",										//30
	"そこで朝が来なくなった理由を求めてアイシャは妖人界へと旅立った"//31
};

StoryPreGameScene::StoryPreGameScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl)
{
	_imgN = 0;
	_counter = 0;
	_charN = 0;
	int size = sizeof(txtDat) / sizeof(char*);
	char fname[256];
	for (int i = 0; i < size; i++) {
		sprintf(fname, "dat/image/storyPreGame/%02d.jpg", i);
		_imgList.push_back(LoadGraph(fname));
	}
	_imgBackground = LoadGraph("dat/image/story/back.jpg");
	_imgTxtBack = LoadGraph("dat/image/storyPreGame/txtBack.png");
	_font  = CreateFontToHandle(FONT, 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_font2 = CreateFontToHandle(FONT, 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_txtColor = GetColor(200,200,200);
}

StoryPreGameScene::~StoryPreGameScene()
{
	int size = _imgList.size();
	for (int i = 0; i < size; i++) {
		DeleteGraph(_imgList[i]);
	}
	DeleteGraph(_imgBackground);
	DeleteGraph(_imgTxtBack);

	DeleteFontToHandle(_font);
	DeleteFontToHandle(_font2);
}

bool StoryPreGameScene::update()
{
	_counter++;
	if (Pad::getIns()->get(ePad::shot)==1) {
		_imgN++;
		_counter = 0;
		_charN = 0;
	}
	if (Pad::getIns()->get(ePad::bom) == 1) {
		SE::getIns()->setPlay(eSE::eSE_cancel);
		_imgN--;
		if (_imgN<0) {
			_imgN = 0;
		}
		_counter = 10000;
		_charN = 0;
	}
	if(Pad::getIns()->get(ePad::start)==1){
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
		return false;
	}
	if (_imgN >= _imgList.size()) {
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
		return false;
	}
	if (strlen(txtDat[_imgN]) >_charN && _counter%2) {
		_charN++;
		if (txtDat[_imgN][_charN]<0) {
			_charN++;
		}
	}
	return false;
}

void StoryPreGameScene::draw()
{
	if (_imgN >= _imgList.size()) {
		return;
	}
	char txt[256];
	strcpy(txt,txtDat[_imgN]);
	txt[_charN] = 0;
	DrawGraph(0, 0, _imgBackground, FALSE);
	DrawGraph(40,860,_imgTxtBack, TRUE);
	DrawStringToHandle(120, 886, txt, _txtColor, _font);
	int w = 0, h = 0;
	GetGraphSize(_imgList[_imgN], &w, &h);
	int x = (WIN_W - w) / 2, y = (WIN_H - h) / 2;
	if (_imgN != 0) {
		DrawGraph(x, 100, _imgList[_imgN - 1], FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _counter * 5);
	DrawGraph(x, 100, _imgList[_imgN], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawStringToHandle(5, WIN_H - 18, "ショットキー:進む　ボムキー:戻る　スタートキー(Esc):スキップ", GetColor(255,255,255), _font2);
}
