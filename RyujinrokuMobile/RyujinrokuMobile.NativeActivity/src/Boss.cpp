#include "Boss.h"
#include <DxLib.h>
#include "GameCounter.h"
#include "BarrageHard.h"
#include "BarrageNormal.h"
#include "BarrageEasy.h"
#include "Define.h"
#include "DebugMode.h"
#include "Keyboard.h"
#include <list>
#include "Utils.h"
#include "SE.h"
#include "GameData.h"
#include "Image.h"
#include "DebugMode.h"
#include "BulletKilledEffectMgr.h"
#include "SavedData.h"
#include "SavedBarrageData.h"

using namespace std;

#include "BossPrm.hpp"

#define BOSS_BARRAGE_TIME 50


Boss::Boss(
	Player* player,
	ItemRegistable* impl,
	BulletEffectRegistable* implB,
	IBackgroundChanger *implBackgroundChanger,
	IResetChapterListener* implResetChapter,
	IShakeListener* implShake,
	int spellPracticeSpellID,
	bool isFromPractice
)
{
	_isFromPractice = isFromPractice;
	_barrageClearNForSaveData = 0;
	_isPlayBacked = false;
	_isAvailable = false;
	_isDrawHp = true;
	_hp = _hpMax = 1;
	_x = INIT_X;
	_y = INIT_Y;
	_invicible = 0;
	_isDead = true;
	_isFinal = false;
	_implItemRegistable = impl;
	_implBulletEffect = implB;
	_implBackgroundChanger = implBackgroundChanger;
	_barrage = nullptr;
	_mover = nullptr;
	_waiter = nullptr;
	_runBoss = nullptr;
	_chapterData = nullptr;
	_barrageN = 0;
	_implResetChapter = implResetChapter;
	_implShake = implShake;
	_spellPracticeSpellID = spellPracticeSpellID;
	_counter = 0;
	_level = GameData::getIns()->level;
	_stage = GameData::getIns()->stage;
	_range = 55;
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone]) {
		_range += 23;
	}
	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Pheromone2]) {
		_range += 23;
	}
	_appearN = 0;
	_barrageN = 0;
	_barrageID = 0;
	_barrageClearN = 0;
	_getSpellcardEffect = nullptr;
	_spellcardbonus = 0;

	_player = player;
	_laserMgr = new LaserMgr(player);

	_chapterData = ChapterData::read(GameData::getIns()->stage,GameData::getIns()->level);
	if (_chapterData != nullptr && !_isFromPractice) {
		if (_chapterData->isBoss) {
			resetChapter();
			_barrageClearNForSaveData = _chapterData->bossClearNForSaveData;
		}
		else {
			GameCounter::getIns()->set(_chapterData->gameCounter);
		}
	}

	int cnt = GameCounter::getIns()->get();
	if (APPEAR_TIME[_stage][1]<cnt) {
		_appearN = 2;
	}
	else if (APPEAR_TIME[_stage][0]<cnt) {
		_appearN = 1;
	}
	else {
		_appearN = 0;
	}

	int n = 0;
	for (int i = 0; i < _stage; i++) {
		n += BOSS_DEAD_N[i];
	}
	_barrageID = n;
	if (_appearN != 0) {
		_barrageID += BOSS_CLEAR_N[_stage][_appearN - 1];
		_barrageN = BOSS_CLEAR_N[_stage][_appearN - 1];
		_barrageClearN = _barrageN;
	}
	if (_barrageClearNForSaveData > 0) {
		_barrageID += _barrageClearNForSaveData;
		_barrageN += _barrageClearNForSaveData;
		_barrageClearN += _barrageClearNForSaveData;
	}
	if (_chapterData != nullptr && _chapterData->isBoss && !_isFromPractice) {
		appear(true);
	}

//	_barrageID = 81;

	char fileName[256];
	sprintf(fileName, "dat/image/boss/%02d.png", _stage);
	_img = LoadGraph(fileName);
	_imgHp = LoadGraph("dat/image/boss/hp.png");
	_imgHpSpell = LoadGraph("dat/image/boss/hpSpell.png");
	_imgHpMax = LoadGraph("dat/image/boss/hpMax.png");
	_font = CreateFontToHandle(FONT, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_time.setTime(BOSS_BARRAGE_TIME * 60);
	_spellMAXTime = (BOSS_BARRAGE_TIME * 60);

	//スペルプラクティス時の特殊処理
	if (_spellPracticeSpellID != -1)
	{
		int n = 0;
		for (int i = 0; i < _stage; i++) {
			n += BOSS_DEAD_N[i];
		}
		n += _spellPracticeSpellID;
		_barrageID = n;
		_barrageN = _spellPracticeSpellID;
		_barrageClearN = _barrageN;
		appear();
	}
	if (_stage == eStageEX) {
		_imgEX[BOSS_IMAGE_YOHI] = LoadGraph("dat/image/boss/00.png");
		_imgEX[BOSS_IMAGE_TOKO] = LoadGraph("dat/image/boss/01.png");
		_imgEX[BOSS_IMAGE_YUYUMI] = LoadGraph("dat/image/boss/02.png");
		_imgEX[BOSS_IMAGE_DAKKI] = LoadGraph("dat/image/boss/03.png");
		_imgEX[BOSS_IMAGE_LAUNCHAR] = LoadGraph("dat/image/boss/launcher2.png");
	}
	resetHp();
}

void Boss::createBarrage()
{
	if (_barrage != nullptr) {
		delete _barrage;
	}
	switch (_level) {
	case eLevel_Easy:
		_barrage = new BarrageEasy(this, _barrageID, _player, _implBulletEffect);
		break;
	case eLevel_Normal:
		_barrage = new BarrageNormal(this, _barrageID, _player, _implBulletEffect);
		break;
	case eLevel_Hard:
		_barrage = new BarrageHard(this, _barrageID, _player, _implBulletEffect);
		break;
	}
	SavedBarrageData::getIns()->increment(SPELL_NAME[_stage][_barrageN], eSavedBarrageDataType_TryedNum, _level);
	_spellcardWatcher.clear();
	_spellcardbonus = GameData::getIns()->scoreBase[GameData::getIns()->eScoreGetSpellcard];
	createChapter();
}

void Boss::updateHitPlayerShot()
{
	list<shared_ptr<PlayerShot>>* shotList = _player->getShotList();
	for (list<shared_ptr<PlayerShot>>::iterator it = shotList->begin(); it != shotList->end();) {
		bool isHit = false;
		if (_hpMax != INF_HP) {
			float x = (*it)->getX();
			float y = (*it)->getY();
			float v = (*it)->getV();
			float angle = (*it)->getAngle();
			float range = (*it)->getRange();
			if (_isAvailable) {
				if (Utils::isHit(x, y, v, angle, range, _x, _y, _range)) {
					_hp -= _invicible == 0 ? (*it)->getPower() : 0;
					GameData::getIns()->plusScore(1.0, GameData::eScoreAttackEnemy);
					if (_hp <= 0) {
						SE::getIns()->stopPlay(eSE_hanabiFukidashi);
						SE::getIns()->stopPlay(eSE_hanabiFukidashi2);
						endBarrage();
						return;
					}
					it = shotList->erase(it);
					isHit = true;
					_implBulletEffect->registBulletEffect(_x, _y);
					if (this->getResidualHp() >= 15) {
						SE::getIns()->setPlay(eSE_hit);
					}
					else {
						SE::getIns()->setPlay(eSE_hitFinal);
					}
				}
			}
		}
		if (!isHit) {
			it++;
		}
	}
	{//プレイヤーのレーザー
		if (_player->isLaserNowShooting()) {
			if (_hpMax != INF_HP) {
				bool isHit = false;
				bool isShift = Pad::getIns()->get(ePad::slow) > 0 ? true : false;
				float x1 = _player->getX() + (isShift ? PLAYER_LASER_W_SLOW_ITVL : PLAYER_LASER_W_ITVL);
				float y1 = _player->getY();
				if (y1 > _y && _x - _range < x1 && x1 < _x + _range) {
					_hp -= _player->getLaserDamageValue();
					_implBulletEffect->registBulletEffect(x1, _y);
					isHit = true;
				}
				float x2 = _player->getX() - (isShift ? PLAYER_LASER_W_SLOW_ITVL : PLAYER_LASER_W_ITVL);
				float y2 = _player->getY();
				if (y2 > _y && _x - _range < x2 && x2 < _x + _range) {
					_hp -= _player->getLaserDamageValue();
					_implBulletEffect->registBulletEffect(x2, _y);
					isHit = true;
				}
				if (_hp <= 0) {
					SE::getIns()->stopPlay(eSE_hanabiFukidashi);
					SE::getIns()->stopPlay(eSE_hanabiFukidashi2);
					endBarrage();
					return;
				}
				if (isHit) {
					if (this->getResidualHp() >= 15) {
						SE::getIns()->setPlay(eSE_hit);
					}
					else {
						SE::getIns()->setPlay(eSE_hitFinal);
					}
				}
			}
		}
	}
	if (_hpMax != INF_HP && _player->isBombing()) {
		float px = _player->getX();
		float py = _player->getY();
		float pr = _player->getBombR();
		if (px - pr <= _x && _x <= px + pr && _y <= py) {
			_hp -= _invicible==0?_player->getBombPower():0;
			GameData::getIns()->plusScore(1.0, GameData::eScoreAttackEnemy);
			if (_hp <= 0) {
				SE::getIns()->stopPlay(eSE_hanabiFukidashi);
				SE::getIns()->stopPlay(eSE_hanabiFukidashi2);
				endBarrage();
				return;
			}
		}
	}
}

void Boss::resetHp()
{
	_hp = HP[_level][_stage][_barrageN];
	_hpMax = _hp;
}

void Boss::endBarrage()
{
	_barrageN++;
	_barrageID++;
	_barrageClearN++;
	_barrageClearNForSaveData++;
	_player->finishBomb();
	if (isChangedBossWhenEXLast()) {
		_talkMgr->enable();
		_x = INIT_X;
		_y = INIT_Y;
		setPos(BOSS_DEFAULT_X, BOSS_DEFAULT_Y, 80);
		_musicMgr->stop();
		SE::getIns()->setPlay(eSE::eSE_dieBoss);
	}
	_isFinal = BOSS_DEAD_N[_stage] == _barrageN+1;
	if (_spellcardWatcher.get()) {
		if (_getSpellcardEffect != nullptr) {
			delete _getSpellcardEffect;
			_getSpellcardEffect = nullptr;
		}
		SavedBarrageData::getIns()->increment(SPELL_NAME[_stage][_barrageN-1], eSavedBarrageDataType_ClearedNum, _level);
		if (SPELL_BACK[_stage][_barrageN-1] == 1) {
			int type = _stage;
			if (_stage == eStageEX) {
				type = EX_BOSS_APPEAR_TYPE[_barrageN - 1];
			}
			_getSpellcardEffect = new GetSpellcardEffect(_spellcardbonus, type);
			GameData::getIns()->plusScore(_spellcardbonus, GameData::eScoreGetSpellcard);
		}
	}
	if (_spellPracticeSpellID == -1) {
		changeBackground(_isFinal);
	}
	if (BOSS_CLEAR_N[_stage][_appearN] == _barrageN || _spellPracticeSpellID != -1) {
		_barrageClearNForSaveData = 0;
		_isDrawHp = false;
		SE::getIns()->setPlay(eSE::eSE_dieBoss);
		if (_appearN == 0 || _appearN == 1) {
			_implShake->onShake(eShakeType::eShakeType_BOSS_DEAD);
		}
		else {
			_implShake->onShake(eShakeType::eShakeType_BOSS_LAST_DEAD);
		}
		if (BOSS_CLEAR_N[_stage][2] == _barrageN && GameData::getIns()->isPractice==false) {
			_talkMgr->enable();
		}
		if (_waiter == nullptr) {
			if (DebugMode::getIns()->isON) {
				_waiter = new Waiter(1);
			}
			else {
				_waiter = new Waiter(120);
			}
		}
		dropItem(_x, _y);
	}
	else {
		initialize();
		_implItemRegistable->regist(_x, _y, eItemPopType::eItemPopType_MoneyMany);
	}
	if (_stage == eStage5 && BOSS_DEAD_N[_stage]-1 == _barrageN) {
		_musicMgr->stop();
		_musicMgr->playSP();
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage5SP);
	}
	if (BOSS_DEAD_N[_stage]-1 == _barrageN) {
		SE::getIns()->setPlay(eSE::eSE_spell);
	}
	if (BOSS_DEAD_N[_stage] == _barrageN || _spellPracticeSpellID != -1) {
		_isDead = true;
	}
	if (_stage == eStageEX &&  BOSS_CLEAR_N[4][1] == _barrageN) {
		_isDead = true;
	}
	resetHp();
	if (_barrage != nullptr) {
		delete _barrage;
	}
	_barrage = nullptr;
	_laserMgr->unregistAll();
	_time.setTime(BOSS_BARRAGE_TIME *60);
	_spellMAXTime = (BOSS_BARRAGE_TIME * 60);
}

bool Boss::initialize()
{
	int time = 80;
	if (DebugMode::getIns()->isON) {
		time = 1;
	}
	setPos(BOSS_DEFAULT_X, BOSS_DEFAULT_Y, time);
	_spellCutIn.initialize(SPELL_NAME[_stage][_barrageN]);
	return false;
}


void Boss::changeBackground(bool isFinal){_implBackgroundChanger->changeBackground(SPELL_BACK[_stage][_barrageN] == 1, isFinal);}

void Boss::disableSpellcardGettable()
{
	_spellcardWatcher.disable();
}

Boss::~Boss()
{
	DeleteGraph(_img);
	DeleteGraph(_imgHp);
	DeleteGraph(_imgHpSpell);
	DeleteGraph(_imgHpMax);
	DeleteFontToHandle(_font);
	delete _laserMgr;
	delete _chapterData;
	if (_mover != nullptr) {
		delete _mover;
	}
	if (_getSpellcardEffect != nullptr) {
		delete _getSpellcardEffect;
	}
}

void Boss::appear(bool noInit)
{
	GameCounter::getIns()->lock();
	_isAvailable = true;
	_isDrawHp = true;
	_counter = 0;
	_isDead = false;
	if (!noInit) {
		initialize();
		createChapter();
	}
}

bool Boss::update() {
	_counter++;
	if (_getSpellcardEffect != nullptr) {
		if (!_getSpellcardEffect->update()) {
			delete _getSpellcardEffect;
			_getSpellcardEffect = nullptr;
		}
	}
	if (_runBoss != nullptr) {
		if (_runBoss->update() == false) {
			delete _runBoss;
			_runBoss = nullptr;
		}
	}
	if (!_isAvailable) {
		for (int i = 0; i < APPEAR_N; i++) {
			if (GameCounter::getIns()->get() == APPEAR_TIME[_stage][i]) {
				appear();
				if (i == 2) {//ラスボスなら
					markPlayedMusic();
				}
				break;
			}
		}
	}
	else {
		if (!_isDead) {
			GameCounter::getIns()->lock();
			if (_barrage != nullptr) {
				_barrage->update();
				updateHitPlayerShot();
				_time.update();
				if (_time.isTimeOver()) {
					endBarrage();
				}
			}
			updateHit();
		}
	}
	if (_spellCutIn.update() == false) {

	}
	if (_mover!=nullptr) {
		if (_mover->update() == false) {
			delete _mover;
			_mover = nullptr;
			if (_barrage == nullptr) {
				if (_isFinal) {
					_waiter = new Waiter(160);
				}
				else {
					int time = 80;
					if (DebugMode::getIns()->isON) {
						time = 1;
					}
					_waiter = new Waiter(time);
				}
			}
		}
	}
	_laserMgr->update();
	if (_waiter!=nullptr) {
		if (!_talkMgr->isAvailable()) {
			if (_waiter->update() == false) {
				delete _waiter;
				_waiter = nullptr;
				if (_isDrawHp) {
					createBarrage();
					_isPlayBacked = false;
				}
				else {
					_runBoss = new RunBoss(this);
					_isAvailable = false;
					_implResetChapter->onCreateChapter();
					_appearN++;
					GameCounter::getIns()->unlock();
					return false;
				}
			}
		}
	}
	if (DebugMode::getIns()->isON) {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_S) == 1) {
			if (_runBoss != nullptr) {
				_x = 0;
				_y = RunBoss::Y;
				delete _runBoss;
				_runBoss = nullptr;
			}
			GameCounter::getIns()->set(APPEAR_TIME[_stage][_appearN]-10);
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Q) == 1) {
			if (_barrage != nullptr) {
				endBarrage();
			}
			else {
				if (_mover != nullptr) {
					delete _mover;
					_mover = nullptr;
				}
				if (_waiter != nullptr) {
					delete _waiter;
					_waiter = nullptr;
				}
				createBarrage();
				endBarrage();
			}
		}
	}
	if (_invicible > 0)	_invicible--;

	if (SPELL_BACK[_stage][_barrageN] == 1 && _barrage != NULL && _barrage->getCounter() >= 600)	//時間でスコアボーナス減少(10秒過ぎたら)
	{
		if (_hpMax != INF_HP)	//耐久ならスペカボーナス減らない
		{
			_spellcardbonus -= GameData::getIns()->scoreBase[GameData::getIns()->eScoreGetSpellcard] / _spellMAXTime;
			if (_spellcardbonus < 0) _spellcardbonus = 0;
		}
	}
	return true;
}

void Boss::draw() {
	if (_getSpellcardEffect != nullptr) {
		_getSpellcardEffect->draw();
	}
	if (_isDead) {
		return;
	}
	if (_isAvailable || _runBoss != nullptr || _invicible%2==0 ) {

		DrawGraph(_x-IMG_POS_W/2,WIN_H-IMG_POS_H,Image::getIns()->bossPos, TRUE);

		if (_stage == eStageEX) {
			drawEX();
		}
		else {
			if (_hpMax==INF_HP) {

			}
			else {
				SetDrawMode(DX_DRAWMODE_BILINEAR);
				DrawRotaGraphF(_x, _y + sin(PI * 2 / 120 * _counter) * 8, 1.0, 0.0, _img, TRUE);
				SetDrawMode(DX_DRAWMODE_NEAREST);
			}
		}
	}
}

void Boss::drawEX() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawRotaGraphF(_x, _y + sin(PI * 2 / 120 * _counter) * 8, 1.0, 0.0, _imgEX[EX_BOSS_IMAGE_TYPE[_barrageClearN]], TRUE);
	if (EX_BOSS_IMAGE_TYPE[_barrageN] == BOSS_IMAGE_LAUNCHAR) {
		float x, y;
		x = _x;
		x += cos(PI2 / 120 * _counter) * 60;
		y = _y + sin(PI * 2 / 120 * _counter) * 8;
		y += sin(PI2 / 97 * _counter) * 60;
		DrawRotaGraphF(x, y, 0.4, 0.0, _imgEX[BOSS_IMAGE_LAUNCHAR], TRUE);
		x = _x;
		x += cos(PI2 / 117 * _counter) * 60;
		y = _y + sin(PI * 2 / 120 * _counter) * 8;
		y += sin(PI2 / 197 * _counter) * 60;
		DrawRotaGraphF(x, y, 0.2, 0.0, _imgEX[BOSS_IMAGE_LAUNCHAR], TRUE);
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void Boss::drawBack()
{
	if (_isDead) {
		return;
	}
	if (_isAvailable || _runBoss != nullptr) {
		int img00 = Image::getIns()->bossRing00;
		int img01 = Image::getIns()->bossRing01;
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraphF(_x, _y, 0.6 + sin(PI * 2 / 180 * _counter)*0.1, -PI * 2 / 300 * _counter, img00, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 150 + sin(PI * 2 / 240 * _counter) * 70);
		DrawRotaGraphF(_x, _y, 0.6 + sin(PI * 2 / 180 * _counter)*0.1, -PI * 2 / 300 * _counter, img01, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraphF(_x, _y, 1.0 + sin(PI * 2 / 180 * _counter)*0.1, PI * 2 / 400 * _counter, img00, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 150 + sin(PI * 2 / 240 * _counter) * 70);
		DrawRotaGraphF(_x, _y, 1.0 + sin(PI * 2 / 180 * _counter)*0.1, PI * 2 / 400 * _counter, img01, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}

void Boss::drawBarrage()
{
	if (_isDead) {
		return;
	}
	if (!_isAvailable) {
		return;
	}
	if (_isDrawHp) {
		if (_player->getY() < 256) {	//プレイヤーが上方にいるときは薄くする
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		}
		int clearedN = SavedBarrageData::getIns()->get(SPELL_NAME[_stage][_barrageN], eSavedBarrageDataType_ClearedNum, _level);
		int tryedN = SavedBarrageData::getIns()->get(SPELL_NAME[_stage][_barrageN], eSavedBarrageDataType_TryedNum, _level);
		if (_barrage != nullptr) {
			DrawFormatStringToHandle(IN_X, 5, GetColor(255, 255, 255), _font, "[%d/%d]", clearedN, tryedN);
		}
		bool isSpell = false;

		{//HP表示サークル
			isSpell = SPELL_BACK[_stage][_barrageN] ? true : false;
			if (isSpell) {
				DrawCircleGauge(_x, _y, 100., Image::getIns()->hpRingBackSpell);
			}
			else {
				DrawCircleGauge(_x, _y, 100., Image::getIns()->hpRingBack);
			}
			DrawCircleGauge(_x, _y, (double)_hp / _hpMax * 100, Image::getIns()->hpRing);
			//		Utils::DrawReversibleCircleGauge(_x, _y, 1.0, Image::getIns()->hpRing, (double)_hp / _hpMax * 100, 0.0);
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		/*
		{//HP表示
		for (int i = 0; i < HP_W; i++) {
		DrawGraph(HP_X + i, HP_Y, _imgHpMax, FALSE);
		}
		int img = SPELL_BACK[_stage][_barrageN] ? _imgHpSpell : _imgHp;
		for (int i = 0; i < HP_W*_hp / _hpMax; i++) {
		DrawGraph(HP_X + i, HP_Y, img, FALSE);
		}
		}
		*/
		{//HP表示画面下部
			int color = isSpell ? GetColor(255, 0, 0) : GetColor(0, 0, 255);
			int w = (IN_W - 2) * _hp / _hpMax;
			DrawBox(IN_X, IN_Y + IN_H + 7, IN_X + IN_W, IN_Y + IN_H + 7 + 5, color, FALSE);
			DrawBox(IN_X + 1, IN_Y + IN_H + 7 + 1, IN_X + w, IN_Y + IN_H + 7 + 5 - 1, GetColor(255, 255, 255), TRUE);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	_laserMgr->draw();
	if (_barrage != nullptr) {
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		_barrage->draw();
		SetDrawMode(DX_DRAWMODE_NEAREST);
//		if (_barrageN != 0) {
			if(_player->getY() < 256)	//プレイヤーが上方にいるときは薄くする
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			DrawStringToHandle(HP_X, IN_Y+5, SPELL_NAME[_stage][_barrageN], GetColor(255, 255, 255), _font);	
			if (SPELL_BACK[_stage][_barrageN] == 1)
			{
				DrawFormatStringToHandle(OUT_W - 400, 20, GetColor(255, 255, 255), _font, "BONUS");
				DrawFormatStringToHandle(OUT_W - 300, 20, GetColor(255, 255, 255), _font, "%d", _spellcardWatcher.get() == true ? _spellcardbonus : 0);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//		}
	}
	_spellCutIn.draw();
	if (_barrage != nullptr) {
		_time.draw();
	}
	drawStar();
}

void Boss::drawStar()
{
	int n = BOSS_CLEAR_N[_stage][_appearN] - _barrageN;
	for (int i = n - 1, j = 0; i >= 0; i--, j++) {
		int id = BOSS_CLEAR_N[_stage][_appearN]-1;
		int img = Image::getIns()->star[SPELL_BACK[_stage][id-j]];
		if (_player->getY() < 150) {	//プレイヤーが上方にいるときは薄くする
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		}
		DrawGraph(IN_X + IN_W - 25 - 18 * j, IN_Y, img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Boss::setTalkMgr(TalkMgr * mgr, bool chapterIsBoss)
{
	_talkMgr = mgr;
	if (_appearN == 2 && chapterIsBoss) {
		_talkMgr->skip();
	}
}

float Boss::getDefaultX()
{
	return BOSS_DEFAULT_X;
}

float Boss::getDefaultY()
{
	return BOSS_DEFAULT_Y;
}

void Boss::setPos(float x, float y, int time)
{
	if (_mover != nullptr) {
		delete _mover;
	}
	_mover = new BossMover(this,x,y,time);
}

float Boss::getResidualHp()
{
	if (_hpMax == 0) {
		return 0.0f;
	}
	return (float)_hp / _hpMax * 100;
}

float getLen(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1)*(x2 - x1)+(y2 - y1)*(y2 - y1));
}

void Boss::moveBit(float moveLen)
{
	while (true) {
		float x = _x + randf2(moveLen+20);
		float y = _y + randf2(moveLen+20);
		if (x < IN_X + 80 || IN_X+IN_W - 80 < x) {
			continue;
		}
		if (y < BOSS_DEFAULT_Y - 80 || BOSS_DEFAULT_Y + 100 < y) {
			continue;
		}
		float len = getLen(_x, _y, x, y);
		if (len < moveLen) {
			continue;
		}
		else {
			setPos(x, y, 60);
			break;
		}
	}
}

void Boss::moveBitMiddle(float moveLen)
{
	while (true) {
		float x = _x + randf2(moveLen + 20);
		float y = BOSS_DEFAULT_Y+120;
		if (x < IN_X + 150 || IN_X + IN_W - 150 < x) {
			continue;
		}
		float len = getLen(_x, _y, x, y);
		if (len < moveLen) {
			continue;
		}
		else {
			setPos(x, y, 60);
			break;
		}
	}
}

void Boss::registLaser(Laser * laser)
{
	_laserMgr->regist(laser);
}

std::list<Laser*>* Boss::getLaserList()
{
	return _laserMgr->getList();
}

int Boss::getEndCount()
{
	return APPEAR_TIME[_stage][2];
}

int Boss::getStartTalkCount()
{
	return APPEAR_TIME[_stage][2];
}

const int * Boss::getSaveCount()
{
	if (_stage < 0 || eStage_Num <= _stage) {
		return NULL;
	}
	return APPEAR_TIME[_stage];
}

bool Boss::isChangedBossWhenEXLast() {
	if (GameData::getIns()->stage == eStageEX) {
		if (BOSS_CLEAR_N[_stage][_appearN] == _barrageN) {
			return false;
		}
		if (_barrageClearN > 0 && GameCounter::getIns()->get() > APPEAR_TIME[_stage][2]) {
			if (EX_BOSS_IMAGE_TYPE[_barrageClearN-1]!=EX_BOSS_IMAGE_TYPE[_barrageClearN]) {
				return true;
			}
		}
	}
	return false;
}

void Boss::markPlayedMusic()
{
	switch (_stage) {
	case eStage1:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage1Boss);
		break;
	case eStage2:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage2Boss);
		break;
	case eStage3:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage3Boss);
		break;
	case eStage4:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage4Boss);
		break;
	case eStage5:
		SavedData::getIns()->markPlayedMusic(eMusicType_Stage5Boss);
		break;
	case eStageEX:
//		SavedData::getIns()->markPlayedMusic(eMusicType_EXBoss);
		break;
	case eStagePH:
		SavedData::getIns()->markPlayedMusic(eMusicType_PHBoss);
		break;
	}
}

void Boss::updateHit()
{
	if (_isAvailable && _hpMax!=INF_HP && !_isDead && _player->isInvincible()==false) {
		float w = _player->getX() - _x;
		float h = _player->getY() - _y;
		float r = _player->getHitRange() + 30;
		if (w*w+h*h<r*r) {
			_player->die();
		}
	}
}

void Boss::createChapter()
{
	if (_chapterData != nullptr) {
		delete _chapterData;
	}
	GameData::getIns()->usedBombItemNum = 0;
	_chapterData = new ChapterData(
		(eStage)_stage,
		(eLevel)_level,
		true,
		GameData::getIns()->power,
		GameData::getIns()->bomb,
		GameData::getIns()->score,
		GameData::getIns()->point,
		GameData::getIns()->graze,
		GameCounter::getIns()->get(),
		GameData::getIns()->scoreBreakdown,
		_barrageClearNForSaveData);
	if (eStage1<=_stage&&_stage<=eStage5) {
		if (!_isFromPractice) {
			_chapterData->save();
		}
	}
}

void Boss::resetChapter()
{
	GameData::getIns()->power = _chapterData->power;
	GameData::getIns()->bomb  = _chapterData->bomb;
	GameData::getIns()->score = _chapterData->score;
	GameData::getIns()->point = _chapterData->point;
	GameData::getIns()->graze = _chapterData->graze;
	GameCounter::getIns()->set(_chapterData->gameCounter);
	_x = BOSS_DEFAULT_X;
	_y = BOSS_DEFAULT_Y;
	if (_mover != nullptr) {
		delete _mover;
		_mover = nullptr;
	}
	_player->reset();
	resetHp();
	if (_waiter != nullptr) {
		delete _waiter;
	}
	_waiter = new Waiter(160);
	if (_barrage != nullptr) {
		delete _barrage;
	}
	_barrage = nullptr;
	_laserMgr->unregistAll();
	_isPlayBacked = true;
	_time.setTime(BOSS_BARRAGE_TIME * 60);
	_spellMAXTime = (BOSS_BARRAGE_TIME * 60);
	BulletKilledEffectMgr::getIns()->initialize();
	_chapterData->preTime = GetNowCount();
	_chapterData->subTime = 0;
}

bool Boss::isSP()
{
	if (_stage == eStage5 && _barrageN == BOSS_DEAD_N[_stage] - 1) {
		return true;
	}
	return false;
}

void Boss::dropItem(float x, float y)
{
	//中ボス2の時
	if (_stage == eStageEX || _stage == eStagePH) {
		_implItemRegistable->regist(x, y, eItemPopType::eItemPopType_MoneyMany);
		_implItemRegistable->regist(x, y, eItemPopType::eItemPopType_Bomb);
	}
	else if (_stage == eStage5) {
		_implItemRegistable->regist(x, y, eItemPopType::eItemPopType_Bomb);
	}
	else {
		_implItemRegistable->regist(x, y, eItemPopType::eItemPopType_BombParts);
	}
}

bool Boss::isLastBoss(int spellN)
{
	if (spellN >= BOSS_CLEAR_N[_stage][1]) {
		return true;
	}
	else {
		return false;
	}
}

int Boss::getExBossType()
{
	return EX_BOSS_APPEAR_TYPE[_barrageN];
}

bool Boss::isInvinsible()
{
	return _hp==INF_HP;
}

