#include "Image.h"
#include <DxLib.h>
#include "GameData.h"

Image::Image()
{
	player[0] = myLoadGraph("dat/image/player/body/静止0.png");
	bossPos = myLoadGraph("dat/image/boss/bossPos.png");
	bossDeathParticle = myLoadGraph("dat/image/boss/particle.png");
	board = myLoadGraph("dat/image/board/board.png");
	hpRingBack = myLoadGraph("dat/image/boss/hpRingBack.png");
	hpRing = myLoadGraph("dat/image/boss/hpRing.png");
	hpRingBackSpell = myLoadGraph("dat/image/boss/hpRingBackSpell.png");
	hpRingSpell = myLoadGraph("dat/image/boss/hpRingSpell.png");
	myLoadDivGraph("dat/image/enemy/00.png", 9, 3, 3, 54, 54, enemyNormal);
	myLoadDivGraph("dat/image/enemy/01.png", 9, 3, 3, 160, 120, enemyBig);
	playerShot00 = myLoadGraph("dat/image/player/bullet00.png");
	playerShot01 = myLoadGraph("dat/image/player/bullet01.png");
	playerBall = myLoadGraph("dat/image/player/bulletBall.png");
	playerRing = myLoadGraph("dat/image/player/ring.png");
	myLoadDivGraph("dat/image/enemy/disappear.png", 5, 5, 1, 40, 140, enemyDisappear);
	bulletDisappear = myLoadGraph("dat/image/bullet/disappear.png");
	launcher[0] = myLoadGraph("dat/image/boss/launcher.png");
	launcher[1] = myLoadGraph("dat/image/boss/launcher5.png");
	launcher[2] = myLoadGraph("dat/image/boss/launcher3.png");
	launcher[3] = myLoadGraph("dat/image/boss/launcher4.png");
	launcherHanabi = myLoadGraph("dat/image/boss/launcherHanabi.png");
	myLoadDivGraph("dat/image/item/00.itemPower.png", 2, 2, 1, 70, 70, item[eItem_Power]);
	myLoadDivGraph("dat/image/item/01.itemScore.png", 2, 2, 1, 70, 70, item[eItem_Score]);
	myLoadDivGraph("dat/image/item/02.itemMoney.png", 2, 2, 1, 70, 70, item[eItem_Money]);
	myLoadDivGraph("dat/image/item/03.itemEmpty.png", 2, 2, 1, 30, 30, item[eItem_Empty]);
	myLoadDivGraph("dat/image/item/04.itemBomb.png", 2, 2, 1, 70, 70, item[eItem_Bomb]);
	myLoadDivGraph("dat/image/item/05.itemBombParts.png", 2, 2, 1, 70, 70, item[eItem_BombParts]);
	myLoadDivGraph("dat/image/enemy/enemyRotate.png", 2, 2, 1, 32, 32, enemyRotate);
	bossRing00 = myLoadGraph("dat/image/boss/bossRing00.png");
	bossRing01 = myLoadGraph("dat/image/boss/bossRing01.png");
	theLast = myLoadGraph("dat/image/boss/theLast.png");
	myLoadDivGraph("dat/image/bullet/laserBody.png", 2, 2, 1, 60, 920, laserBody);
	myLoadDivGraph("dat/image/bullet/laserRoot.png", 2, 2, 1, 140, 140, laserRoot);
	star[0] = myLoadGraph("dat/image/board/star.png");
	star[1] = myLoadGraph("dat/image/board/starSpell.png");
	enemyAppear = myLoadGraph("dat/image/enemy/appear.png");
	enemyHp = myLoadGraph("dat/image/enemy/hp.png");
	enemyHpBack = myLoadGraph("dat/image/enemy/hpBack.png");
	enemyHpBackShort = myLoadGraph("dat/image/enemy/hpBackShort.png");
	myLoadDivGraph("dat/image/number/boardNumber.png", 10, 10, 1, 14, 25, boardNumber);
	myLoadDivGraph("dat/image/board/boardFont.png", 5, 1, 5, 112, 33, boardFont);
	myLoadDivGraph("dat/image/player/laser.png", 5, 5, 1, 30, 45, playerLaser);
	playerLaserRoot = myLoadGraph("dat/image/player/laserRoot.png");
	playerLaserMain = myLoadGraph("dat/image/player/laserMain.png");
	myLoadDivGraph("dat/image/menu/level/level2.png", eLevel_Num, 1, 3, 120, 40, level);
	myLoadDivGraph("dat/image/menu/level/sho.png", eStage_Num, 1, eStage_Num, 63, 30, stageSho);
	getSpellcard[0] = myLoadGraph("dat/image/spellcard/spellcard1.png");
	getSpellcard[1] = myLoadGraph("dat/image/spellcard/spellcard2.png");
	getSpellcard[2] = myLoadGraph("dat/image/spellcard/spellcard3.png");
	getSpellcard[3] = myLoadGraph("dat/image/spellcard/spellcard4.png");
	getSpellcard[4] = myLoadGraph("dat/image/spellcard/spellcard5.png");
	getSpellcard[5] = myLoadGraph("dat/image/spellcard/spellcardEX.png");
	getSpellcardFont = myLoadGraph("dat/image/spellcard/spellcardMoji.png");
	itemGetBorderLine = myLoadGraph("dat/image/board/itemGetBorderLine.png");
	graze = myLoadGraph("dat/image/player/graze.png");
	myLoadDivGraph("dat/image/player/shotLaser.png", 5, 5, 1, 60, 90, playerShotLaser);
//	myLoadDivGraph("dat/image/player/laser.png", 5, 5, 1, 30, 34, playerShotLaser);
}

Image::~Image()
{
}

int Image::myLoadGraph(char *fileName)
{
	int ret = LoadGraph(fileName);
	_images.push_back(ret);
	return ret;
}

int Image::myLoadDivGraph(char *fileName, int n, int xn, int yn, int w, int h, int* buf){
	int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
	for (int i = 0; i < n; i++) {
		_images.push_back(buf[i]);
	}
	return 0;
}

void Image::load() {
}

void Image::release() {
	int size = _images.size();
	for (int i = 0; i < size; i++) {
		DeleteGraph(_images[i]);
	}
	_images.clear();
}