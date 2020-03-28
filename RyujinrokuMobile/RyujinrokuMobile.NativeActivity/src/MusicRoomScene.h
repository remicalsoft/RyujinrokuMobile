#pragma once
#include "Scene.h"
#include "MusicMgr.h"
#include "MusicSelectUtils.h"
#include <vector>

enum eMusicType {
	eMusicType_Title,
	eMusicType_Stage1,
	eMusicType_Stage1Boss,
	eMusicType_Stage2,
	eMusicType_Stage2Boss,
	eMusicType_Stage3,
	eMusicType_Stage3Boss,
	eMusicType_Stage4,
	eMusicType_Stage4Boss,
	eMusicType_Stage5,
	eMusicType_Stage5Boss,
	eMusicType_Stage5SP,
	eMusicType_Endroll,
	eMusicType_EX,
	eMusicType_PH,
	eMusicType_PHBoss,
	eMusicType_Omake,

	//MUSIC_NUM(50)個まで拡張可能
	eMusicType_Num
};

class MusicRoomScene : public Scene {

	int _imgTitle;
	int _imgBack;
	int _selectID;
	int _playingID;
	int _bgm;
	int _counter;
	int _font, _fontText;
	int _colorSelected, _colorOther;
	std::vector<std::string*> _txt;

	MusicSelectUtil *_selector;

	void load(bool able=true);
	void release();
	void playSoundRoom(int id);

public:
	const static int MUSIC_NUM = 50;

	MusicRoomScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~MusicRoomScene();
	bool update() override;
	void draw() override;
};

typedef struct {
	char musicName[64];
	char musicPath[64];
	int musicLoop;
} music_t;