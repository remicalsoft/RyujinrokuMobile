#include "GameScene.h"
#include "Image.h"
#include "GameCounter.h"
#include "BarrageZakoEasy.h"
#include "BarrageZakoNormal.h"
#include "BarrageZakoHard.h"
#include "SE.h"
#include "Calculator.h"
#include "ImageBullet.h"
#include "TalkMgr.h"
#include "TalkMgrEX.h"
#include "BulletEffectMgr.h"
#include "Utils.h"
#include "BulletKilledEffectMgr.h"
#include "GameData.h"
#include "Keyboard.h"
#include "DebugMode.h"
#include "SceneStoryParam.h"
#include "BackgroundFactory.h"
#include "GameScenePrm.h"
#include "Replayer.h"
#include "Define.h"
#include "SavedData.h"
#include "DebugMode.h"
#include "BossPrm.hpp"

using namespace std;

GameScene::GameScene(ISceneChangedListener* impl, ScenePrmBase* prm) : Scene(impl) {
	GameData::getIns()->usedBombItemNum = 0;
	_theLast = nullptr;
	_title = nullptr;
	_chapterData = nullptr;
	_enemyMgr = nullptr;
	_itemMgr = nullptr;
	_cutIn = nullptr;
	_isNowSpell = false;
	_spellPracticeSpellID = -1;
	_isFromPractice = false;
	int stage = DebugMode::getIns()->switchStage();
	GameScenePrm *p = dynamic_cast<GameScenePrm*>(prm);
	if (p != nullptr) {
		GameData::getIns()->stage = stage != -1 ? stage : p->_stage;
		GameData::getIns()->level = p->_level;
		_isFromPractice = p->_isFromPractice;
		_spellPracticeSpellID = p->_spellPracticeSpellID;
	}
	_stage = stage != -1 ? stage : GameData::getIns()->stage;
	if (_stage == eStage1 || _stage == eStageEX || _stage == eStagePH) {
		init();
		GameData::getIns()->power = 0;
		GameData::getIns()->bomb = BOMB_PARTS_N * 2;
	}
	_level = GameData::getIns()->level;

	setupReplay();

	GameCounter::getIns()->initialize();
	_player = new Player(this, this, _isFromPractice, _spellPracticeSpellID != -1);

	_pause = new Pause(_isFromPractice, _spellPracticeSpellID != -1, impl, this);
	Calculator::getIns()->setPlayerInstance(_player);
	BackgroundFactory::create(_stage, &_background, &_backgroundSpell);
	_boss = new Boss(_player, this, this, this, this, this, _spellPracticeSpellID, _isFromPractice);
	//	_boss->createChapter();
	_player->setBoss(_boss);

	bool isBoss = false;
	if(!Replayer::getIns()->isReplaying()){
		_chapterData = ChapterData::read(_stage, _level);
		if (_chapterData != nullptr && !_isFromPractice) {
			resetChapter();
			isBoss = _chapterData->isBoss;
			Replayer::getIns()->disable();
		}
		else {
			_enemyMgr = new EnemyMgr((BarrageRegistable*)this, _player, this, this);
			_enemyMgr->initialize();
			_title = new Title(_stage);
			_itemMgr = new ItemMgr(_player);
		}
		SavedData::getIns()->dat.havePlayed[_stage] = true;
	}
	else {
		_enemyMgr = new EnemyMgr((BarrageRegistable*)this, _player, this, this);
		_enemyMgr->initialize();
		_title = new Title(_stage);
		_itemMgr = new ItemMgr(_player);
	}

	_chapterClear = new ChapterClear(_boss);
	Calculator::getIns()->setBossInstance(_boss);
	_musicMgr = new MusicMgr(_stage);
	_boss->setMusicMgr(_musicMgr);
	if (_stage == eStageEX) {
		_talkMgr = new TalkMgrEX(&_gameEnding, _musicMgr, _boss);
	}
	else {
		_talkMgr = new TalkMgr(&_gameEnding, _musicMgr, _boss);
	}
	_boss->setTalkMgr(_talkMgr, isBoss);
	_boss->changeBackground(false);
	if (_boss->isSP()) {
		_musicMgr->playSP();
	}
	else if (_spellPracticeSpellID != -1) {
		if (_stage == eStageEX) {
			int type = _boss->getExBossType();
			_musicMgr->setBossPlayedN(type);
			if (type == eStageEX) {
				_musicMgr->play(false);
			}
			else {
				_musicMgr->play(true);
			}
		}
		else if (_boss->isLastBoss(_spellPracticeSpellID)) {
			_musicMgr->play(true);
		}
		else {
			_musicMgr->play(false);
		}
	}
	else {
		_musicMgr->play(_boss->isFinalAppeared() && isBoss);
	}
	_board.setEndCount(_boss->getEndCount());
	_player->setTalkStatusGettable(this);

	if (_chapterData == nullptr) {
		createChapter();
	}
	markMusicPlayed();
}

GameScene::~GameScene() {
	delete _player;
	delete _background;
	delete _backgroundSpell;
	delete _enemyMgr;
	delete _title;
	delete _boss;
	delete _itemMgr;
	delete _talkMgr;
	delete _musicMgr;
	delete _cutIn;
	delete _theLast;
	delete _chapterClear;
	delete _pause;
	if (_chapterData != nullptr) {
		delete _chapterData;
	}
	if (Replayer::getIns()->isRecoding()) {
		if (_isFromPractice || _spellPracticeSpellID != -1) {
			Replayer::getIns()->endRecode(true);
		}
		else {
			switch (_stage) {
			case eStage5:
			case eStageEX:
			case eStagePH:
			{
				Replayer::getIns()->endRecode(true);
				break;
			}
			}
		}
	}
}

void GameScene::init() {
	GameData::getIns()->bomb = 0;
	GameData::getIns()->power = 0;
	GameData::getIns()->graze = 0;
	GameData::getIns()->point= 0;
	GameData::getIns()->retryCount = 0;
	GameData::getIns()->score = 0;
	memset(GameData::getIns()->scoreBreakdown,0,sizeof(GameData::getIns()->scoreBreakdown));
}

void GameScene::setupReplay()
{
	if (!Replayer::getIns()->isReplaying()) {
		if (ChapterData::exists(_stage, _level)) {
			Replayer::getIns()->disable();
		}
		switch (_stage) {
		case eStage1:
		case eStageEX:
		case eStagePH:
			if (!ChapterData::exists(_stage, _level)) {
				Replayer::getIns()->enable();
			}
			break;
		}
	}
	if (_isFromPractice || _spellPracticeSpellID != -1) {	//練習ではステージに応じてパワーを与えておく
		init();
		switch (_stage) {
		case eStage1:
		case eStage2:
		case eStage3:
		case eStage4:
		case eStage5:
			GameData::getIns()->bomb = 2*BOMB_PARTS_N + _stage*BOMB_PARTS_N;
			GameData::getIns()->power = _stage*100;
			break;
		case eStageEX:
			GameData::getIns()->bomb = 2 * BOMB_PARTS_N;
			GameData::getIns()->power = 0;
			break;
		case eStagePH:
			GameData::getIns()->bomb = 2 * BOMB_PARTS_N;
			GameData::getIns()->power = 0;
			break;
		}
	}

	if (Replayer::getIns()->isReplaying()) {
		switch (_stage) {
		case eStage1:
		case eStageEX:
		case eStagePH:
			Replayer::getIns()->setSrand();
			break;
		}
	}
	else if(Replayer::getIns()->isDefault()){
		eReplayType replayType = eReplayType_Normal;
		if (_isFromPractice) {
			replayType = eReplayType_Practice;
		}
		else if (_spellPracticeSpellID != -1) {
			replayType = eReplayType_SpellPractice;
		}

		int seed = GetNowCount();
		SRand(seed);
		srand(seed);
		Replayer::getIns()->startRecode(seed, replayType);
		Replayer::getIns()->setStage((eStage)_stage);
		Replayer::getIns()->setLevel((eLevel)GameData::getIns()->level);
	}
	else {
		//nothing
	}
}

void GameScene::markMusicPlayed()
{
	switch (_stage) {
	case eStage1:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage1);
		break;
	case eStage2:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage2);
		break;
	case eStage3:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage3);
		break;
	case eStage4:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage4);
		break;
	case eStage5:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage5);
		break;
	case eStageEX:
		SavedData::getIns()->markPlayedMusic(eMusicType_EX);
		break;
	case eStagePH:
		SavedData::getIns()->markPlayedMusic(eMusicType_PH);
		break;
	}
}

bool GameScene::update() {
//	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_L) == 1)
//		printfDx("%d\n",GetRand(10000));

	if (Replayer::getIns()->isRecoding()) {
		Replayer::getIns()->recode();
	}
	else if(Replayer::getIns()->isReplaying()) {
		if (!Replayer::getIns()->updatePadStatus()) {
			Replayer::getIns()->endReplay();
			_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
			return false;
		}
	}
	else {
		//nothing
	}
	{
		ChapterData* data = _chapterData;
		if (_boss->isAvailable()) {
			data = _boss->getChapterData();
		}
		if (_pause->update(data) == false)	//falseが帰ってきたらタイトルに戻る
		{
			return false;
		}
		if (_pause->isPause()) {
			return true;
		}
	}
	_musicMgr->update();
	_title->update();
//	if (_isNowSpell) {
		_backgroundSpell->update();
//	} else {
		_background->update();
//	}
	if (_cutIn != nullptr) {
		if (_cutIn->update() == false) {
			delete _cutIn;
			_cutIn = nullptr;
		}
	}
	if (_theLast != nullptr) {
		if (_theLast->update() == false) {
			delete _theLast;
			_theLast = nullptr;
		}
	}
	if (_spellPracticeSpellID == -1) {
		_enemyMgr->update();
	}
	_player->update();
	_board.update();
	_bulletEffectMgr.update();
	for (list<Barrage*>::iterator it = _barrageList.begin(); it != _barrageList.end();) {
		if ((*it)->update() == false) {
			delete (*it);
			it = _barrageList.erase(it);
		}
		else {
			it++;
		}
	}
	_itemMgr->update();
	_talkMgr->update();
	bool isBossAllive = _boss->update();
	if(_spellPracticeSpellID != -1 && isBossAllive==false)	//ボスが倒されたらスペプラは終了する
		_gameEnding.enable();

	if (!_boss->isAvailable()) {
		_bulletEffectMgr.update();
	}
	_chapterClear->update();
	if (_gameEnding.update() == false) {
		if(_isFromPractice==true || _spellPracticeSpellID != -1)	//プラクティス時はプラクティス画面へ戻る
		{
			if (Replayer::getIns()->isReplaying()) {
				Replayer::getIns()->endReplay();
			}
			else if (Replayer::getIns()->isReplaying()){
				Replayer::getIns()->endRecode(true);
			}
			else {
				//nothing
			}
			_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
		}
		else	//ストーリー時は次のステージかEDへ
		{
			int level = GameData::getIns()->level;
			ChapterData::remove(_stage, level);
			SavedData::getIns()->dat.isClearStage[level][_stage] = true;
			GameData::getIns()->stage++;
			if (GameData::getIns()->stage == eStageEX+1) {
				if (Replayer::getIns()->isReplaying()) {
					Replayer::getIns()->endReplay();
					_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
				}
				else if(Replayer::getIns()->isRecoding()){
					Replayer::getIns()->endRecode(true);
					SceneStoryParam p;
					p.gotoEndroll = true;
					_implSceneChanged->onSceneChanged(eScene::ExEd, false, &p);
				}
				else {
					SceneStoryParam p;
					p.gotoEndroll = true;
					_implSceneChanged->onSceneChanged(eScene::ExEd, false, &p);
				}
			}
			else if (GameData::getIns()->stage == eStage5+1) {
				if (Replayer::getIns()->isReplaying()) {
					Replayer::getIns()->endReplay();
					_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, nullptr);
				}
				else if(Replayer::getIns()->isRecoding()){
					Replayer::getIns()->endRecode(true);
					SceneStoryParam p;
					p.gotoEndroll = true;
					_implSceneChanged->onSceneChanged(eScene::Ed, false, &p);
				}
				else {
					SceneStoryParam p;
					p.gotoEndroll = true;
					_implSceneChanged->onSceneChanged(eScene::Ed, false, &p);
				}
			}
			else {
				Replayer::getIns()->clearStage();
				if (Replayer::getIns()->isReplaying()) {
					_implSceneChanged->onSceneChanged(eScene::Game, true, nullptr, 1);
				}
				else {
					_implSceneChanged->onSceneChanged(eScene::Game, false, nullptr);
				}
			}
		}
		return false;
	}
	deleteObject();
	_bossDeathParticleMgr.update();
	BulletKilledEffectMgr::getIns()->update();
	GameCounter::getIns()->update();
	if (DebugMode::getIns()->isON) {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_P) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_P) > 30) {
			GameData::getIns()->power += 10;
			if (GameData::getIns()->power > 500) {
				GameData::getIns()->power = 500;
			}
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_B) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_B) > 30) {
			GameData::getIns()->bomb += 1;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_S) == 1) {
			_enemyMgr->kill();
			for (auto b : _barrageList) {
				b->kill();
			}
		}
	}
	return true;
}

void GameScene::draw() {
	if (_isNowSpell) {
		_backgroundSpell->draw();
	}
	else {
		_background->draw();
	}
	_boss->drawBack();
	_player->draw();
	_enemyMgr->draw();
	_boss->draw();
	_bulletEffectMgr.draw();
	_enemyMgr->drawHp();
	_boss->drawBarrage();
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for (auto b : _barrageList) {
		b->draw();
	}
	_itemMgr->draw();
	BulletKilledEffectMgr::getIns()->draw();
	_player->drawHitMark();
	SetDrawMode(DX_DRAWMODE_NEAREST);
	_title->draw();
	if (_theLast != nullptr) {
		_theLast->draw();
	}
	_bossDeathParticleMgr.draw();
	_board.draw();
	_talkMgr->draw();
	_chapterClear->draw();
	_musicMgr->draw();
	if (_cutIn != nullptr) {
		_cutIn->draw();
	}
	_pause->draw();
	_gameEnding.draw();
	if (DebugMode::getIns()->isON) {
		DrawFormatString(300, 0, GetColor(255, 255, 255), "%d", GameCounter::getIns()->get());
	}
	if (Replayer::getIns()->isReplaying()) {
		Replayer::getIns()->draw();
	}
}

void GameScene::deleteObject()
{
	if (_chapterClear->isChapterFinished()) {
		_enemyMgr->kill();
		for (auto b : _barrageList) {
			b->kill();
			delete b;
		}
		_barrageList.clear();
	}
}

void GameScene::regist(eLevel level, std::shared_ptr<Enemy> enemy, Script const script)
{
	Barrage *barrage = nullptr;
	switch (level) {
	case eLevel_Easy:
		barrage = new BarrageZakoEasy(enemy, script, _player, this);
		break;
	case eLevel_Normal:
		barrage = new BarrageZakoNormal(enemy, script, _player, this);
		break;
	case eLevel_Hard:
		barrage = new BarrageZakoHard(enemy, script, _player, this);
		break;
	}
	_barrageList.push_back(barrage);
}

void GameScene::regist(float x, float y, eItemPopType popType)
{
	_itemMgr->regist(x, y, popType);
}

void GameScene::registBulletEffect(float x, float y)
{
	_bulletEffectMgr.regist(x, y);
}

void GameScene::registBulletEffect(float x, float y, eBulletEffectType type)
{
	_bulletEffectMgr.regist(x, y, type);
}

void GameScene::changeBackground(bool isSpell, bool isFinal)
{
	_isNowSpell = isSpell;
	if (isFinal) {
		_theLast = new TheLast();
	}
	else if (isSpell) {
		if (_cutIn != nullptr) {
			delete _cutIn;
		}
		_cutIn = new CutIn(_talkMgr->getCutInImage());
	}
	else {
		//nothing
	}
}

bool GameScene::isNowTalking()
{
	return _talkMgr->isAvailable();
}

void GameScene::onResetChapter()
{
	if (_boss->isAvailable()) {
		_boss->resetChapter();
		_player->reset();
	}
	else {
		resetChapter();
	}
	_chapterData->preTime = GetNowCount();
	_chapterData->subTime = 0;
}

void GameScene::onCreateChapter()
{
	if (_chapterData != nullptr) {
		delete _chapterData;
	}
	GameData::getIns()->usedBombItemNum = 0;
	_chapterData = new ChapterData(
		(eStage)_stage,
		(eLevel)_level,
		false,
		GameData::getIns()->power,
		GameData::getIns()->bomb,
		GameData::getIns()->score,
		GameData::getIns()->point,
		GameData::getIns()->graze,
		GameCounter::getIns()->get()+1,
		GameData::getIns()->scoreBreakdown);
	GameData::getIns()->retryCount = 0;
	if (eStage1 <= _stage&&_stage <= eStage5) {
		if (!_isFromPractice) {
			_chapterData->save();
		}
	}
}

void GameScene::createChapter()
{
	if (_chapterData != nullptr) {
		delete _chapterData;
	}
	GameData::getIns()->usedBombItemNum = 0;
	_chapterData = new ChapterData(
		(eStage)_stage,
		(eLevel)_level,
		false,
		GameData::getIns()->power,
		GameData::getIns()->bomb,
		GameData::getIns()->score,
		GameData::getIns()->point,
		GameData::getIns()->graze,
		GameCounter::getIns()->get(),
		GameData::getIns()->scoreBreakdown);
	GameData::getIns()->retryCount = 0;
	if (eStage1 <= _stage&&_stage <= eStage5) {
		if (!_isFromPractice) {
			_chapterData->save();
		}
	}
}

void GameScene::resetChapter()
{
	GameData::getIns()->retryCount++;
	GameData::getIns()->power = _chapterData->power;
	GameData::getIns()->bomb  = _chapterData->bomb;
	GameData::getIns()->score = _chapterData->score;
	GameData::getIns()->point = _chapterData->point;
	GameData::getIns()->graze = _chapterData->graze;
	GameCounter::getIns()->set(_chapterData->gameCounter);
	for (int i = 0; i < GameData::eScoreType_Num; i++)
	{
		GameData::getIns()->scoreBreakdown[i] = _chapterData->scoreBreakdown[i];
	}

	if (_enemyMgr != nullptr) {
		delete _enemyMgr;
	}
	_enemyMgr = new EnemyMgr((BarrageRegistable*)this, _player, this, this);
	_enemyMgr->initialize();
	if (_title != nullptr) {
		delete _title;
	}
	_title = new Title(_stage);
	_player->reset();
	if (_itemMgr != nullptr) {
		delete _itemMgr;
	}
	_itemMgr = new ItemMgr(_player);
	for (auto b : _barrageList) {
		delete b;
	}
	_barrageList.clear();
	_bulletEffectMgr.Initialize();
	BulletKilledEffectMgr::getIns()->initialize();
	_player->clearGrazeEffect();
	if (APPEAR_TIME[_stage][0] + 1 == GameCounter::getIns()->get() || APPEAR_TIME[_stage][1] + 1 == GameCounter::getIns()->get()) {
		_boss->dropItem(BOSS_DEFAULT_X, BOSS_DEFAULT_Y);
	}
}

void GameScene::readChapter()
{
}

void GameScene::onPlayerDied()
{
	_pause->onPlayerDied();
}

void GameScene::onShake(eShakeType type)
{
	VECTOR v;
	v.x = 20;
	v.y = 20;
	v.z = 20;
	if (_stage == eStage4 || _stage == eStageEX) {
		v.x = 50;
		v.y = 50;
		v.z = 50;
	}
	int frame = 180;
	switch (type) {
	case eShakeType_BOMB:
		frame = 180;
		break;
	case eShakeType_BOSS_LAST_DEAD:
		_bossDeathParticleMgr.regist(_boss->getX(), _boss->getY());
	case eShakeType_BOSS_DEAD:
		frame = 60;
		v.x *= 1.4;
		v.y *= 1.4;
		v.z *= 1.4;
		break;
	}
	if (_isNowSpell) {
		_backgroundSpell->shake(frame, v);
	}
	else {
		_background->shake(frame, v);
	}
}

