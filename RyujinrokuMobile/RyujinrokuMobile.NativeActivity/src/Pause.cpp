#include "Pause.h"
#include "Pad.h"
#include <DxLib.h>
#include "Define.h"
#include "SE.h"
#include "GameScene.h"
#include "GameScenePrm.h"
#include "GameData.h"
#include "Replayer.h"
#include "Utils.h"
#include "Toast.h"
#include "SavedData.h"

const static int FINISH_COUNT = 64;
const static int DEAD_DISABLE_TIME = 40;

const static int X = 180;

Pause::Pause(bool isPractice, bool isSpellProctice, ISceneChangedListener* impl, IResetChapterListener* implChapter)
{
	_isSpellPractice = isSpellProctice;
	_startTime = 0;
	_isPractice = isPractice;
	_implSceneChanger = impl;
	_implResetChapter = implChapter;
	_isPause = false;
	_isFinalized = false;
	_isCanceled = false;
	_isPlayerDied = false;
	_counter = 0;
	_finalizeCounter = 0;
	_cancelCounter = 0;
	_selectID = ePauseSelect_BackToGame;

	_imgs[0] = LoadGraph("dat/image/board/pause_select00.png");
	_imgs[1] = LoadGraph("dat/image/board/pause_select01.png");
	_imgs[2] = LoadGraph("dat/image/board/pause_select02.png");
	_imgs[3] = LoadGraph("dat/image/board/pause_select03.png");
	_imgs[4] = LoadGraph("dat/image/board/pause_select04.png");

//	LoadDivGraph("dat/image/board/pause_select.png", ePauseGraphicNum, 1, ePauseGraphicNum, 354, 35, _imgs);
}


Pause::~Pause()
{
	for (int i = 0; i < _items.size(); i++) {
		delete _items[i];
	}
	for (int i = 0; i < ePauseGraphicNum; i++) {
		DeleteGraph(_imgs[i]);
	}
}

void restoreBombItem() {
	if (GameData::getIns()->usedBombItemNum > 0) {
		if (GameData::getIns()->usedBombItemNum == 2) {
			SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb2] = true;
			SavedData::getIns()->dat.hasEquipableItem[eEquipItem_Bomb2] = true;
		}
		else {
			if (SavedData::getIns()->dat.hasEquipableItem[eEquipItem_Bomb] == false) {
				SavedData::getIns()->dat.hasEquipableItem[eEquipItem_Bomb] = true;
				SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb] = true;
			}
			else {
				SavedData::getIns()->dat.hasEquipableItem[eEquipItem_Bomb2] = true;
				SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb2] = true;
			}
		}
	}
}

bool Pause::update(ChapterData* chapterData) {
	if(_isPause == true)
	{
		if (_isPractice || _isSpellPractice)	//プラクティス時はプラクティス画面へ戻る
		{
			Replayer::getIns()->endRecode(false);
			_implSceneChanger->onSceneChanged(eScene::SceneDelete, true, nullptr);
			return false;
		}

		if (!_isFinalized && !_isCanceled) {
			if (_isPlayerDied) {
				if (_counter > DEAD_DISABLE_TIME*1.6) {
					if (Pad::getIns()->get(ePad::down) == 1) {
						_items[_selectID]->disable();
						_selectID = (_selectID + 1) % eDiedPauseSelect_Num;
						_items[_selectID]->enable();
						     SE::getIns()->setPlay(eSE::eSE_upDown);
					}
					if (Pad::getIns()->get(ePad::up) == 1) {
						_items[_selectID]->disable();
						_selectID = (_selectID + (eDiedPauseSelect_Num - 1)) % eDiedPauseSelect_Num;
						_items[_selectID]->enable();
						     SE::getIns()->setPlay(eSE::eSE_upDown);
					}
				}
			}
			else {
				if (Pad::getIns()->get(ePad::down) == 1) {
					_items[_selectID]->disable();
					_selectID = ((_selectID + 1) % ePauseSelect_Num);
					_items[_selectID]->enable();
					     SE::getIns()->setPlay(eSE::eSE_upDown);
				}
				if (Pad::getIns()->get(ePad::up) == 1) {
					_items[_selectID]->disable();
					_selectID = ((_selectID + (ePauseSelect_Num - 1)) % ePauseSelect_Num);
					_items[_selectID]->enable();
					     SE::getIns()->setPlay(eSE::eSE_upDown);
				}
				if (Pad::getIns()->get(ePad::bom) == 1 || Pad::getIns()->get(ePad::start) == 1) {
					SE::getIns()->setPlay(eSE::eSE_cancel);
					for (int i = 0; i < _items.size(); i++) {
						_items[i]->cancel();
					}
					_isCanceled = true;
					chapterData->subPauseTime(GetNowCount()-_startTime);
				}
			}
			if (Pad::getIns()->get(ePad::shot) == 1) {
				if (!_isPlayerDied || _counter > DEAD_DISABLE_TIME) {
					for (int i = 0; i < _items.size(); i++) {
						_items[i]->finalize();
					}
					_isFinalized = true;
					SE::getIns()->setPlay(eSE::eSE_selectDetail);
				}
			}
		}
		if (_isFinalized) {
			_finalizeCounter++;
		}
		if (_finalizeCounter == FINISH_COUNT) {
			if (!(!_isPlayerDied && (_selectID == ePauseSelect_BackToGame))) {
				if (!Replayer::getIns()->isReplaying()) {
					chapterData->subPauseTime(GetNowCount() - _startTime);
					int getMoney = Utils::convertPlayTimeToMoney(chapterData->getRealPlayTime());
					GameData::getIns()->addMoney(getMoney);
					if (getMoney > 0) {
						Toast::getIns()->add(string((to_string(getMoney) + "円拾いました")));
					}
				}
			}
			if (_isPlayerDied) {
				switch (_selectID)
				{
				case eDiedPauseSelect_RetryLastChapter:
					restoreBombItem();
					_isPlayerDied = false;
					_isPause = false;
					_implResetChapter->onResetChapter();
					chapterData = nullptr;
					_isCanceled = false;
					break;
				case eDiedPauseSelect_RetryStart:
				{
					restoreBombItem();
					//リプレイを停止
					//リプレイを保存するか確認	
					eStage stage = (eStage)GameData::getIns()->stage;
					switch (stage) {
					case eStage1:
					case eStage2:
					case eStage3:
					case eStage4:
					case eStage5:
						stage = eStage1;
					}
					GameScenePrm prm(stage, (eLevel)GameData::getIns()->level);
					if (Replayer::getIns()->isRecoding()) {
						Replayer::getIns()->endRecode(false);
					}
					ChapterData::remove(stage, (eLevel)GameData::getIns()->level);
					_implSceneChanger->onSceneChanged(eScene::Game, false, &prm);
					return false;
				}
				break;
				case eDiedPauseSelect_BackToTitle:
				{
					restoreBombItem();
					//				Replayer::getIns()->endRecode(false);
					Replayer::getIns()->endRecode(true);
					Replayer::getIns()->endReplay();

					if (_isPractice || _isSpellPractice)	//プラクティス時はプラクティス画面へ戻る
					{
						_implSceneChanger->onSceneChanged(eScene::SceneDelete, true, nullptr);
					}
					else	//ストーリー時はタイトル
					{
						_implSceneChanger->onSceneChanged(eScene::Menu, false, nullptr);
					}
					return false;
				}
				break;
				default:
					ERR("Pause::updateで不明な_selectID");
					break;
				}
				return true;

			}
			else {
				switch (_selectID)
				{
				case ePauseSelect_BackToGame:
					_isPause = false;
					_isCanceled = false;
					chapterData->subPauseTime(GetNowCount() - _startTime);
					break;
				case ePauseSelect_RetryStart:
				{
					//リプレイを停止
					//リプレイを保存するか確認	
					eStage stage = (eStage)GameData::getIns()->stage;
					switch (stage) {
					case eStage1:
					case eStage2:
					case eStage3:
					case eStage4:
					case eStage5:
						stage = eStage1;
					}
					GameScenePrm prm(stage, (eLevel)GameData::getIns()->level);
					Replayer::getIns()->endRecode(false);
					ChapterData::remove(stage, (eLevel)GameData::getIns()->level);
					_implSceneChanger->onSceneChanged(eScene::Game, false, &prm);
					return false;
				}
				break;
				case ePauseSelect_BackToTitle:
				{
					//				Replayer::getIns()->endRecode(false);
					Replayer::getIns()->endRecode(true);
					Replayer::getIns()->endReplay();

					if (_isPractice || _isSpellPractice)	//プラクティス時はプラクティス画面へ戻る
					{
						_implSceneChanger->onSceneChanged(eScene::SceneDelete, true, nullptr);
					}
					else	//ストーリー時はタイトル
					{
						_implSceneChanger->onSceneChanged(eScene::Menu, false, nullptr);
					}
					return false;
				}
				break;
				default:
					ERR("Pause::updateで不明な_selectID");
					break;
				}
				return true;
			}
		}
		if (_isCanceled) {
			_cancelCounter++;
		}
		if (_cancelCounter == FINISH_COUNT/2) {
			_isPause = false;
			return true;
		}
		for (int i = 0; i < _items.size(); i++) {
			if (!_isPlayerDied || _counter > DEAD_DISABLE_TIME) {
				_items[i]->update();
			}
		}
		_counter++;
	}
	else
	{
		if (Pad::getIns()->get(ePad::start)==1) {
			_isPause = !_isPause;
			//ポーズ開始時に初期化
			_isFinalized = false;
			_isCanceled = false;
			_counter = 0;
			_finalizeCounter = 0;
			_cancelCounter = 0;
			_selectID = ePauseSelect_BackToGame;
			_startTime = GetNowCount();
			for (auto i : _items) {
				delete i;
			}
			_items.clear();
			_items.push_back(new LevelItem(X, 600 + 64 * 0, _imgs[ePauseGraphic_BackToGame], true));
			_items[0]->setPos(X, 600 + 64 * 0);
			if (GameData::getIns()->stage <= eStage5) {
				_items.push_back(new LevelItem(X, 600 + 64 * 1, _imgs[ePauseGraphic_BackToTitle], false));
			}
			else {
				_items.push_back(new LevelItem(X, 600 + 64 * 1, _imgs[ePauseGraphic_BackToTitleEX], false));
			}
			_items[1]->setPos(X, 600 + 64 * 1);
			_items.push_back(new LevelItem(X, 600 + 64 * 2, _imgs[ePauseGraphic_RetryStart], false));
			_items[2]->setPos(X, 600 + 64 * 2);
		}
	}
	return true;
}

void Pause::draw()
{
	if (_isPause) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0,0,WIN_W,WIN_H,GetColor(0,0,0),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

		bool isBrended = false;
		for (int i = 0; i < _items.size(); i++) {
			_items[i]->draw();
		}
	}
}

void Pause::onPlayerDied()
{
	_isPlayerDied = true;
	_isPause = true;
	_isFinalized = false;
	_isCanceled = false;
	_counter = 0;
	_finalizeCounter = 0;
	_cancelCounter = 0;
	_selectID = eDiedPauseSelect_RetryLastChapter;
	_startTime = GetNowCount();
	for (auto i : _items) {
		delete i;
	}
	_items.clear();
	_items.push_back(new LevelItem(X, 600 + 64 * 0, _imgs[ePauseGraphic_RetryLastChapter], true));
	_items[0]->setPos(X, 600 + 64 * 0);
	if (GameData::getIns()->stage <= eStage5) {
		_items.push_back(new LevelItem(X, 600 + 64 * 1, _imgs[ePauseGraphic_BackToTitle], false));
	}
	else {
		_items.push_back(new LevelItem(X, 600 + 64 * 1, _imgs[ePauseGraphic_BackToTitleEX], false));
	}
	_items[1]->setPos(X, 600 + 64 * 1);
	_items.push_back(new LevelItem(X, 600 + 64 * 2, _imgs[ePauseGraphic_RetryStart], false));
	_items[2]->setPos(X, 600 + 64 * 2);
}
