#pragma once

#include "Scene.h"
#include "Player.h"
#include "Board.h"
#include "Background.h"
#include "EnemyMgr.h"
#include "BarrageRegistable.h"
#include <list>
#include "Barrage.h"
#include "Define.h"
#include "ISceneChangedListener.h"
#include "ScenePrmBase.h"
#include "Title.h"
#include "TalkMgr.h"
#include "Boss.h"
#include "BulletEffectMgr.h"
#include "ItemRegistable.h"
#include "ItemMgr.h"
#include "BulletEffectRegistable.h"
#include "ChapterClear.h"
#include "GameEnding.h"
#include "MusicMgr.h"
#include "IBackgroundChanger.h"
#include "CutIn.h"
#include "TheLast.h"
#include "Pause.h"
#include "ITalkStatusGettable.h"
#include "ChapterData.h"
#include "IResetChapterListener.h"
#include "IOnPlayerDiedListener.h"
#include "IShakeListener.h"
#include "BossDeathParticleMgr.h"

class GameScene : 
	public Scene, 
	public BarrageRegistable, 
	public ItemRegistable, 
	public BulletEffectRegistable, 
	public IBackgroundChanger, 
	public ITalkStatusGettable,
	public IResetChapterListener, 
	public IOnPlayerDiedListener,
	public IShakeListener
{
	bool _isNowSpell;
	bool _isFromPractice;
	int _stage;
	int _level;
	int _spellPracticeSpellID;
	Player* _player;
	Board _board;
	TalkMgr* _talkMgr;
	Background *_background;
	Background *_backgroundSpell;
	EnemyMgr *_enemyMgr;
	Title *_title;
	Boss *_boss;
	std::list<Barrage*> _barrageList;
	BulletEffectMgr _bulletEffectMgr;
	ItemMgr *_itemMgr;
	ChapterClear* _chapterClear;
	GameEnding _gameEnding;
	MusicMgr* _musicMgr;
	CutIn *_cutIn;
	TheLast *_theLast;
	Pause *_pause;
	ChapterData* _chapterData;
	BossDeathParticleMgr _bossDeathParticleMgr;

	void init();
	void setupReplay();
	void markMusicPlayed();

public:
	GameScene(ISceneChangedListener* impl, ScenePrmBase* prm);
	~GameScene();
	bool update() override;
	void draw() override;
	void deleteObject();
	void regist(eLevel level, std::shared_ptr<Enemy> enemy, Script script) override;
	void regist(float x, float y, eItemPopType popType) override;
	void registBulletEffect(float x, float y) override;
	void registBulletEffect(float x, float y, eBulletEffectType type);
	void changeBackground(bool isSpell, bool isFinal) override;
	bool isNowTalking() override;
	void onResetChapter() override;
	void onCreateChapter() override;	//createChapterとの違いがわからないです
	void createChapter();
	void resetChapter();
	void readChapter();
	void onPlayerDied() override;
	void onShake(eShakeType type) override;
};

