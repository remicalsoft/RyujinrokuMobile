#pragma once
#include "Task.h"
#include "Barrage.h"
#include "BossMover.h"
#include "Player.h"
#include "ItemRegistable.h"
#include "BulletEffectRegistable.h"
#include "Waiter.h"
#include "RunBoss.h"
#include "IBackgroundChanger.h"
#include "SpellCutIn.h"
#include "LaserMgr.h"
#include "Laser.h"
#include "Time.h"
#include "GetSpellcardEffect.h"
#include "SpellcardWatcher.h"
#include "ISpellcardDisablable.h"
#include "TalkMgr.h"
#include "MusicMgr.h"
#include "ChapterData.h"
#include "IResetChapterListener.h"
#include "IShakeListener.h"

class TalkMgr;
class BossMover;
class RunBoss;
class Laser;
class LaserMgr;
class Barrage;

class Boss :
	public Task, ISpellcardDisablable
{
	int _img, _imgEX[5];
	int _counter;
	int _stage;
	int _barrageN;
	int _barrageID;
	int _appearN;
	int _barrageClearN;//弾幕を撃破した数
	int _barrageClearNForSaveData;
	bool _isAvailable;
	bool _isDrawHp;
	bool _isDead;
	bool _isFinal;
	bool _isPlayBacked;
	float _hp, _hpMax;
	float _range;
	int _level;
	int _imgHp, _imgHpSpell, _imgHpMax;
	int _font;
	int _invicible;
	int _spellPracticeSpellID;
	int _spellcardbonus;
	int _spellMAXTime;
	bool _isFromPractice;

	Barrage* _barrage;
	LaserMgr* _laserMgr;
	BossMover* _mover;
	Player* _player;
	ItemRegistable *_implItemRegistable;
	BulletEffectRegistable* _implBulletEffect;
	Waiter* _waiter;
	RunBoss* _runBoss;
	IBackgroundChanger *_implBackgroundChanger;
	SpellCutIn _spellCutIn;
	Time _time;
	GetSpellcardEffect *_getSpellcardEffect;
	SpellcardWatcher _spellcardWatcher;
	TalkMgr *_talkMgr;
	MusicMgr *_musicMgr;
	ChapterData *_chapterData;
	IResetChapterListener *_implResetChapter;
	IShakeListener* _implShake;

	void createBarrage();
	void updateHitPlayerShot();
	void resetHp();
	void endBarrage();
	bool initialize();
	bool isChangedBossWhenEXLast();
	void markPlayedMusic();
	void updateHit();

public:
	Boss(Player* player,
		ItemRegistable* impl,
		BulletEffectRegistable* implBulletDisappearEffect,
		IBackgroundChanger *implBackgroundChanger,
		IResetChapterListener* implResetChapter,
		IShakeListener* implShake,
		int spellPracticeSpellID,
		bool isFromPractice);
	~Boss();
	float _x, _y;
	bool update() override;
	void draw() override;
	void drawEX();
	void drawBack();
	void drawBarrage();
	void drawStar();
	void setTalkMgr(TalkMgr* mgr, bool chapterIsBoss);
	void setMusicMgr(MusicMgr* mgr) {
		_musicMgr = mgr;
	}
	float getX() { return _x; }
	float getY() { return _y; }
	int getHpMax() { return _hpMax; }
	float getDefaultX();
	float getDefaultY();
	bool isDead() { return _isDead; }
	void setPos(float x, float y, int time);
	float getResidualHp();
	void moveBit(float moveLen);
	void moveBitMiddle(float moveLen);
	void registLaser(Laser* laser);
	bool isAvailable() {
		return _isAvailable;
	}
	bool isBrrageAlive() {
		return _barrage == nullptr ? false : true;
	}
	std::list<Laser*>* getLaserList();
	void setTime(int frame) {
		_time.setTime(frame);
	}
	void setSpellMAXTime(int frame) {
		_spellMAXTime = frame;
	}
	int getReminingTime() {
		return _time.getTime();
	}
	int getEndCount();
	int getStartTalkCount();
	const int* getSaveCount();

	void setInvicibleTime(int time) { _invicible = time; };
	void appear(bool noInit = false);
	void changeBackground(bool isFinal);
	void disableSpellcardGettable() override;
	void createChapter();
	void resetChapter();
	ChapterData* getChapterData() {
		return _chapterData;
	}
	bool isFinalAppeared() {
		return _appearN == 2;
	}
	bool isSP();
	void dropItem(float x, float y);
	bool isLastBoss(int spellN);
	int getExBossType();
	bool isInvinsible();
};
