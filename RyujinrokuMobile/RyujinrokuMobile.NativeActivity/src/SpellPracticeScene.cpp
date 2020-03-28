#include "SpellPracticeScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "SE.h"
#include "GameData.h"
#include "MenuScenePrm.h"
#include "BgmLoopPosDefine.h"
#include "SpellPracticeCursol.h"
#include "SpellPracticeIcon.h"
#include "GameScenePrm.h"
#include "BGM.h"
#include "SavedBarrageData.h"

//大体PracticeSelectSceneからコピペ
const static int FINISH_COUNT = 64;
const static int Width[2] = { 400,200 };	//弾幕名と挑戦回数の横幅
const static int dx = 100;	//左の隙間
const static int Height = 25;

SpellPracticeScene::SpellPracticeScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl) {
	_isFinalized = false;
	_isCanceled = false;
	_isActivated = false;
	_counter = 0;
	_finalizeCounter = 0;
	_cancelCounter = 0;
	_stageSelectID = 0;
	_spellSelectID = 1;
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");

	_font[0] = CreateFontToHandle(FONT, 15, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	_font[1] = CreateFontToHandle(FONT, 50, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	SetFontCacheUsePremulAlphaFlag(true);
	_font[2] = CreateFontToHandle(FONT, 16, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	SetFontCacheUsePremulAlphaFlag(false);
	//項目の画像作成
	LoadDivGraph("dat/image/menu/level/level2.png", eLevel_Num, 1, eLevel_Num, 120, 40, _levelGraph);

	makeItemGraph();
	_items.push_back(new SpellPracticeCursol(getCursolX(_spellSelectID%eLevel_Num), getCursolY(_spellSelectID / eLevel_Num), Width[1], Height));

	MenuScenePrm *p = (MenuScenePrm*)prm;
}

SpellPracticeScene::~SpellPracticeScene() {
	deleteItemGraph();
	DeleteGraph(_imgBack);
	for(int i=0; i<eLevel_Num; i++)
	{
		/*
		for(int j=0; j< BOSS_DEAD_N[i]; j++)
		{
			DeleteGraph(_spellnameGraph[i][j]);
		}
		*/
		DeleteGraph(_levelGraph[i]);
	}
	DeleteFontToHandle(_font[0]);
	DeleteFontToHandle(_font[1]);
	DeleteFontToHandle(_font[2]);
	for (int g : _handleList) {
		DeleteGraph(g);
	}
}


int SpellPracticeScene::getCursolX(int level)
{
	return dx+Width[0] +level*Width[1] + level*2;
}

int SpellPracticeScene::getCursolY(int spellnum)
{
	return 200+ Height*spellnum -Height/2 +spellnum*2;
}

void SpellPracticeScene::makeItemGraph()
{
	SetUsePremulAlphaConvertLoad(true);
	for(int i=0; i<eStage_Num ; i++)
	{
		for(int j=0; j< BOSS_DEAD_N[i]; j++)
		{
			for(int k=0; k< eLevel_Num; k++)
			{
				int handle = MakeScreen( Width[1], Height, TRUE ) ;
				_handleList.push_back(handle);
				SetDrawScreen( handle ) ;

				_items.push_back(new SpellPracticeIcon(getCursolX(k) + Width[1]/2 +WIN_W*i, getCursolY(j)+Height/2, handle));	
			}
		}
	}

	for(int i=0; i<eStage_Num ; i++)
	{
		for(int j=0; j< BOSS_DEAD_N[i]; j++)
		{
			//ステージ名の画像作成
			int spellnameGraph = MakeScreen( Width[0], Height, TRUE ) ;
			_items.push_back(new SpellPracticeIcon( getCursolX(0)-Width[0]/2 +WIN_W*i,  getCursolY(j)+Height/2, spellnameGraph));	
		}
	}
	SetUsePremulAlphaConvertLoad(false);

}

void SpellPracticeScene::deleteItemGraph()
{
	for (int i = 0; i < _items.size(); i++) {
		delete _items[i];
	}
}

void SpellPracticeScene::rewriteItemGraph()
{
	int itr = 0;
	for (int i = 0; i<eStage_Num; i++)
	{
		for (int j = 0; j< BOSS_DEAD_N[i]; j++)
		{
			for (int k = 0; k< eLevel_Num; k++)
			{ 
				if (i >= eStageEX && k == eLevel_Hard)//EX以降はHard(Lunatic)はない ので描画しない 
				{
					itr++;
					continue;	
				}

				SetDrawScreen(((SpellPracticeIcon*)_items[itr])->getimg());
				SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);	//乗算済みアルファ
				FillGraph(((SpellPracticeIcon*)_items[itr])->getimg(),0,0,0,0);

				//薄っすらと背景に難易度別に色をつける
				int c = 0;
				switch (k)
				{
				case eLevel_Easy:	c = GetColor(64, 255, 64);	break;
				case eLevel_Normal:	c = GetColor(64, 64, 255);	break;
				case eLevel_Hard:	c = GetColor(255, 255, 64);	break;
				default:
					ERR("SpellPractice::makeItemGraphで不明なk");
					break;
				}

				SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 192);	//乗算済みアルファ
				DrawBox(0, 0, Width[1], Height, c, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				int clearedN = SavedBarrageData::getIns()->get(SPELL_NAME[i][j], eSavedBarrageDataType_ClearedNum, k);
				int tryedN = SavedBarrageData::getIns()->get(SPELL_NAME[i][j], eSavedBarrageDataType_TryedNum, k);

				DrawFormatStringToHandle(25, 3, GetColor(255, 255, 255), _font[2], "%6d", clearedN);
				DrawFormatStringToHandle(80, 3, GetColor(255, 255, 255), _font[2], "/");
				DrawFormatStringToHandle(95, 3, GetColor(255, 255, 255), _font[2], "%-6d", tryedN);

				itr++;
			}
		}
	}
	for (int i = 0; i<eStage_Num; i++)
	{
		for (int j = 0; j< BOSS_DEAD_N[i]; j++)
		{
			//弾幕名の画像作成
			SetDrawScreen(((SpellPracticeIcon*)_items[itr])->getimg());
			SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);	//乗算済みアルファ
			FillGraph(((SpellPracticeIcon*)_items[itr])->getimg(), 0, 0, 0, 0);

			string name = "？？？";
			if (SavedBarrageData::getIns()->get(SPELL_NAME[i][j], eSavedBarrageDataType_TryedNum, eLevel_Easy) > 0 ||
				SavedBarrageData::getIns()->get(SPELL_NAME[i][j], eSavedBarrageDataType_TryedNum, eLevel_Normal) > 0 ||
				SavedBarrageData::getIns()->get(SPELL_NAME[i][j], eSavedBarrageDataType_TryedNum, eLevel_Hard) > 0)
				name = SPELL_NAME[i][j];
			DrawFormatStringToHandle(0, 3, GetColor(255, 255, 255), _font[2], "%-20s", name.c_str());	//弾幕名

			itr++;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	
	SetDrawScreen(DX_SCREEN_BACK);
}

//現在のステージ、カーソルの位置から、弾幕が上から何番目にあたるかを返す（全難易度を含める）
int SpellPracticeScene::getItemHandle()
{
	int itemhandle=0;

	for(int i=0; i< _stageSelectID; i++)
	{
		itemhandle += BOSS_DEAD_N[i]*eLevel_Num;
	}

	return itemhandle+ _spellSelectID;
}

//弾幕名の画像をitemのハンドルで返す
int SpellPracticeScene::getSpellNameHandle()
{
	int itemhandle= 0;

	//難易度別画像のぶんのカウント
	for(int i=0; i< eStage_Num; i++)
	{
		itemhandle += BOSS_DEAD_N[i]*eLevel_Num;
	}

	//こっから名前画像をカウント
	for(int i=0; i< _stageSelectID; i++)
	{
		itemhandle += BOSS_DEAD_N[i];
	}

	return itemhandle + _spellSelectID%eLevel_Num;
}

//そのステージの全難易度の全弾幕数
int SpellPracticeScene::getMAXSpellNumStage()
{ return BOSS_DEAD_N[_stageSelectID]*eLevel_Num;}

void SpellPracticeScene::updateTarget()
{
	((SpellPracticeCursol*)(_items[_items.size()-1]))->updateTarget(getCursolX(_spellSelectID%eLevel_Num), getCursolY(_spellSelectID/3));
}

bool SpellPracticeScene::update() {
	if (!_isActivated) {
		onResume();
		_isActivated = true;
	}
	_counter++;

	int SelectableStageNum= eStage_Num;	//現在プレイ可能なステージ数　遊んでないステージは選ばれない

	if (!_isFinalized && !_isCanceled) {
		//上下で弾幕選択
		int down = Pad::getIns()->get(ePad::down);
		int up   = Pad::getIns()->get(ePad::up);
		if ( down== 1 || (down >=20 && down%4==0)) {
			_items[ getItemHandle() ]->disable();
			_items[ getSpellNameHandle() ]->disable();
			_spellSelectID = (_spellSelectID + eLevel_Num) % getMAXSpellNumStage();
			_items[ getItemHandle() ]->enable();
			_items[ getSpellNameHandle() ]->enable();
			updateTarget();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		else if ( up== 1 || (up >=20 && up%4==0)){
			_items[ getItemHandle() ]->disable();
			_items[ getSpellNameHandle() ]->disable();
			_spellSelectID = (_spellSelectID + (getMAXSpellNumStage() - eLevel_Num)) % getMAXSpellNumStage();
			_items[ getItemHandle() ]->enable();
			_items[ getSpellNameHandle() ]->enable();
			updateTarget();
			SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		//シフト＋左右でステージ選択
		else if(Pad::getIns()->get(ePad::slow) > 0)
		{
			 if (Pad::getIns()->get(ePad::right) == 1) {
				_items[ getItemHandle() ]->disable();
				_stageSelectID = (_stageSelectID + 1) % SelectableStageNum ;
				if(_spellSelectID >= getMAXSpellNumStage())	//ステージ変更時の下のはみ出し防止
				{
					_spellSelectID = getMAXSpellNumStage()-eLevel_Num + _spellSelectID%eLevel_Num;
					updateTarget();
				}
				if (_stageSelectID >= eStageEX && _spellSelectID%eLevel_Num == eLevel_Hard)	//EX以降はHard(Lunatic)はない
				{
					_spellSelectID--;
					updateTarget();
				}
				_items[ getItemHandle() ]->enable();
				//ラスト以外のアイテムを１ページスクロール
				for(int i=0; i<_items.size()-1; i++)
				{
					((SpellPracticeIcon*)_items[i])->updateTargetX(((SpellPracticeIcon*)_items[i])->getTargetX()- WIN_W);
				}

				SE::getIns()->setPlay(eSE::eSE_upDown);
			}
			else if (Pad::getIns()->get(ePad::left) == 1) {
				_items[ getItemHandle() ]->disable();
				_stageSelectID = (_stageSelectID + (SelectableStageNum - 1)) % SelectableStageNum;
				if(_spellSelectID >= getMAXSpellNumStage())	//ステージ変更時の下のはみ出し防止
				{
					_spellSelectID = getMAXSpellNumStage()-eLevel_Num + _spellSelectID%eLevel_Num;
					updateTarget();
				}
				if (_stageSelectID >= eStageEX && _spellSelectID%eLevel_Num == eLevel_Hard)	//EX以降はHard(Lunatic)はない
				{
					_spellSelectID--;
					updateTarget();
				}
				_items[ getItemHandle() ]->enable();
				//ラスト以外のアイテムを１ページスクロール
				for(int i=0; i<_items.size()-1; i++)
				{
					((SpellPracticeIcon*)_items[i])->updateTargetX(((SpellPracticeIcon*)_items[i])->getTargetX()+ WIN_W);
				}
				SE::getIns()->setPlay(eSE::eSE_upDown);
			}
		}
		//左右で難易度選択
		else if (Pad::getIns()->get(ePad::right) == 1) {
			_items[ getItemHandle() ]->disable();
			_spellSelectID++;
			if (_stageSelectID >= eStageEX && _spellSelectID%eLevel_Num == 2) 	//EX以降はHard(Lunatic)はない
				_spellSelectID -=2;
			else if(_spellSelectID%eLevel_Num ==0)
				_spellSelectID -=3;

			_items[ getItemHandle() ]->enable();
			updateTarget();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		else if (Pad::getIns()->get(ePad::left) == 1) {
			_items[ getItemHandle() ]->disable();
			_spellSelectID--;
			if ((_spellSelectID+3)%eLevel_Num == eLevel_Num-1)
			{
				if(_stageSelectID >= eStageEX)	//EX以降はHard(Lunatic)はない
					_spellSelectID += 2;
				else
					_spellSelectID += 3;
			}
			_items[ getItemHandle() ]->enable();
			updateTarget();
			     SE::getIns()->setPlay(eSE::eSE_upDown);
		}
		else if (Pad::getIns()->get(ePad::shot) == 1) {
			if (SavedBarrageData::getIns()->get(SPELL_NAME[_stageSelectID][_spellSelectID / eLevel_Num], eSavedBarrageDataType_TryedNum, _spellSelectID%eLevel_Num) > 0)	//試行経験ありで練習可
			{
				for (int i = 0; i < _items.size(); i++) {
					_items[i]->finalize();
				}
				_isFinalized = true;
				SE::getIns()->setPlay(eSE::eSE_selectDetail);
			}
			else
				SE::getIns()->setPlay(eSE::eSE_error);
		}
		else if (Pad::getIns()->get(ePad::bom) == 1) {
			SE::getIns()->setPlay(eSE::eSE_cancel);
			for (int i = 0; i < _items.size(); i++) {
				_items[i]->cancel();
			}
			_isCanceled = true;
		}
	}
	if (_isFinalized) {
		_finalizeCounter++;
	}
	if (_finalizeCounter == FINISH_COUNT) {
		BGM::getIns()->stopMenuBGM();
		_finalizeCounter=0;
		_isFinalized = false;
		for (int i = 0; i < _items.size(); i++) {
			_items[i]->reset( true);
		}
		_isActivated = false;
		GameData::getIns()->isPractice = true;
		GameScenePrm prm((eStage)_stageSelectID, (eLevel)(_spellSelectID%eLevel_Num));
		prm._isFromPractice = true;
		prm._spellPracticeSpellID = _spellSelectID / eLevel_Num;
		_implSceneChanged->onSceneChanged(eScene::Game, true, &prm);	
		return false;
	}
	if (_isCanceled) {
		_cancelCounter++;
	}
	if (_cancelCounter == FINISH_COUNT/2) {
		_isActivated = false;
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
		GameData::getIns()->isPractice = false;
		return false;
	}
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->update();
	}
	return true;
}

void SpellPracticeScene::draw() {
	bool isBrended = false;
	DrawGraph(0, 0, _imgBack, FALSE);
	for (int i = 0; i < _items.size(); i++) {
		_items[i]->draw();
	}





	if (_counter < 32) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - _counter * 8);
		isBrended = true;
	}
	if (_finalizeCounter > 16) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (_finalizeCounter - 16) * 16);
		isBrended = true;
	}
	if (_cancelCounter > 16) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (_cancelCounter - 16) * 16);
		isBrended = true;
	}
	if (isBrended) {
		DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//難易度描画
	for (int i = 0; i < eLevel_Num; i++)
	{
		if (_stageSelectID >= eStageEX && i == eLevel_Hard)	//EX以降はHard(Lunatic)はない
			continue;
		DrawRotaGraph(getCursolX(i) + Width[1] / 2, 150, 1, 0, _levelGraph[i], TRUE);
	}

	//ステージ数描画
	DrawFormatStringToHandle(500, 20, GetColor(255, 255, 255), _font[1], _stageSelectID==6 ? "最終章" : "第%d章", _stageSelectID+1);

	DrawFormatStringToHandle(100, 20, GetColor(255, 255, 255), _font[0], "前ページ：Slow＋←");
	DrawFormatStringToHandle(1000, 20, GetColor(255, 255, 255), _font[0], "後ページ：Slow＋→");
}

void SpellPracticeScene::onResume()
{
	BGM::getIns()->startMenuBGM();
	rewriteItemGraph();
}
