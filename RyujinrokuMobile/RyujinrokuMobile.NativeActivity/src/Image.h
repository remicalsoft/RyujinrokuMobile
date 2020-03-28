#pragma once

#include "Singleton.h"
#include "Scene.h"
#include <vector>
#include "Item.h"
#include "Define.h"

class Image : public Singleton<Image> {
	std::vector<int> _images;

	int myLoadGraph(char*);
	int myLoadDivGraph(char *fileName, int n, int xn, int yn, int w, int h, int* buf);

public:
	int theLast;
	int player[1];
	int playerRing;
	int hpRingBack, hpRing, hpRingBackSpell, hpRingSpell;
	int bossPos;
	int bossRing00, bossRing01;
	int bossDeathParticle;
	int board;
	int item[eItem_Num][2];
	int launcher[4];
	int launcherHanabi;
	int enemyRotate[2];
	int enemyNormal[9];
	int enemyBig[9];
	int enemyDisappear[5];
	int enemyHp, enemyHpBack, enemyHpBackShort;
	int bulletDisappear;
	int playerShot00, playerShot01, playerBall;
	int playerShotLaser[5];
	int laserRoot[2], laserBody[2];
	int star[2];
	int enemyAppear;
	int boardNumber[10];
	int boardFont[5];
	int playerLaser[5];
	int playerLaserRoot, playerLaserMain;
	int level[eLevel_Num];
	int stageSho[eStage_Num];
	int getSpellcard[eStage_Num],getSpellcardFont;
	int itemGetBorderLine;
	int graze;
	Image();
	~Image();
	void load();
	void release();
};

